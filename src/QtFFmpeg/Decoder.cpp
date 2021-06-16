#include "qtffmpeg.h"

#define IsNull(item)                  (NULL==(item))
#define NotNull(item)                 (NULL!=(item))
#define nDropOut(Condition)           if (Condition) return
#define nKickOut(Condition,Result)    if (Condition) return (Result)
#define nGreater(A,B)                 ((A)>(B))
#define nLess(A,B)                    ((A)<(B))

FFmpeg::Decoder:: Decoder (void)
{
  Filename      =  ""                               ;
  FormatCtx     =  NULL                             ;
  Dictionary    =  NULL                             ;
  VideoCtx      =  NULL                             ;
  AudioCtx      =  NULL                             ;
  CaptionCtx    =  NULL                             ;
  VideoCodec    =  NULL                             ;
  AudioCodec    =  NULL                             ;
  CaptionCodec  =  NULL                             ;
  Frame         =  NULL                             ;
  RGB           =  NULL                             ;
  AudioFrame    =  NULL                             ;
  Captions      =  NULL                             ;
  VideoStream   =  NULL                             ;
  AudioStream   =  NULL                             ;
  CaptionStream =  NULL                             ;
  ConvertCtx    =  NULL                             ;
  VideoIndex    =    -1                             ;
  AudioIndex    =    -1                             ;
  Subtitle      =    -1                             ;
  Error         =     0                             ;
  isVideo       = false                             ;
  isAudio       = false                             ;
  Resample      =  NULL                             ;
  audioConvert  =  NULL                             ;
  TextCodec     = QTextCodec::codecForName("UTF-8") ;
}

FFmpeg::Decoder::~Decoder (void)
{
}

QString FFmpeg::Decoder::ErrorString(int errnum)
{
  char Err [ 2048 ]                                ;
  memset                   ( Err    , 0   , 2048 ) ;
  ::av_strerror            ( errnum , Err , 2047 ) ;
  return QString::fromUtf8 ( Err                 ) ;
}

QByteArray FFmpeg::Decoder::toNative(QString filename)
{
  QByteArray F                               ;
  QFileInfo  FI ( filename )                 ;
  QString    FN                              ;
  FI . setFile ( filename )                  ;
  if ( ! FI . exists ( ) ) return F          ;
  FN = QDir::toNativeSeparators ( filename ) ;
  if (FN.length()<=0) return F               ;
  F = TextCodec -> fromUnicode  ( FN       ) ;
  return F                                   ;
}

bool FFmpeg::Decoder::StartAudio(QString Filename)
{
  if ( ! Open ( Filename ) ) {
    return false             ;
  }                          ;
  if ( ! FindStream ( ) )    {
    Close ( )                ;
    return false             ;
  }                          ;
  if ( ! FindAudio  ( ) )    {
    Close ( )                ;
    return false             ;
  }                          ;
  if ( ! OpenAudio  ( ) )    {
    Close ( )                ;
    return false             ;
  }                          ;
  return true                ;
}

bool FFmpeg::Decoder::StartVideo(QString Filename)
{
  if ( ! Open ( Filename ) ) {
    return false             ;
  }                          ;
  if ( ! FindStream ( ) )    {
    Close ( )                ;
    return false             ;
  }                          ;
  ////////////////////////////
  if ( ! FindVideo  ( ) )    {
    Close ( )                ;
    return false             ;
  }                          ;
  if ( ! FindAudio  ( ) )    {
    Close ( )                ;
    return false             ;
  }                          ;
  FindCaption ( )            ;
  ////////////////////////////
  if ( ! OpenVideo  ( ) )    {
    Close ( )                ;
    return false             ;
  }                          ;
  if ( ! OpenAudio  ( ) )    {
    Close ( )                ;
    return false             ;
  }                          ;
  OpenCaption ( )            ;
  ////////////////////////////
  return true                ;
}

bool FFmpeg::Decoder::Open(QString filename)
{
  QFileInfo FI ( filename )               ;
  /////////////////////////////////////////
  Filename     = ""                       ;
  VideoIndex   = -1                       ;
  AudioIndex   = -1                       ;
  Subtitle     = -1                       ;
  isVideo      = false                    ;
  isAudio      = false                    ;
  Error        = 0                        ;
  Extras       . clear ( )                ;
  if (!FI.exists())                       {
    Error = AVERROR_EXIT                  ;
    return false                          ;
  }                                       ;
  /////////////////////////////////////////
  QString fn = FI.absoluteFilePath()      ;
  QByteArray NF                           ;
  int        ret                          ;
  NF  = toNative ( fn )                   ;
  if (NotNull(Dictionary))                {
    ret = ::avformat_open_input           (
          &FormatCtx                      ,
          (const char *)NF.constData()    ,
          NULL                            ,
          &Dictionary                   ) ;
  } else                                  {
    ret = ::avformat_open_input           (
          &FormatCtx                      ,
          (const char *)NF.constData()    ,
          NULL                            ,
          NULL                          ) ;
  }                                       ;
  /////////////////////////////////////////
  if (ret<0)                              {
    Error = ret                           ;
    return false                          ;
  }                                       ;
  if (IsNull(FormatCtx))                  {
    Error = AVERROR_DECODER_NOT_FOUND     ;
    return false                          ;
  }                                       ;
  /////////////////////////////////////////
  Filename = fn                           ;
  return true                             ;
}

bool FFmpeg::Decoder::Close(void)
{
  if (NotNull(VideoCtx    )) ::avcodec_close        ( VideoCtx     ) ;
  if (NotNull(AudioCtx    )) ::avcodec_close        ( AudioCtx     ) ;
  if (NotNull(CaptionCtx  )) ::avcodec_close        ( CaptionCtx   ) ;
  if (NotNull(FormatCtx   )) ::avformat_close_input (&FormatCtx    ) ;
  if (NotNull(Frame       )) ::av_free              ( Frame        ) ;
  if (NotNull(RGB         )) ::av_free              ( RGB          ) ;
  if (NotNull(AudioFrame  )) ::av_free              ( AudioFrame   ) ;
  if (NotNull(Captions    )) ::avsubtitle_free      ( Captions     ) ;
  if (NotNull(ConvertCtx  )) ::sws_freeContext      ( ConvertCtx   ) ;
  if (NotNull(Resample    )) ::swr_free             (&Resample     ) ;
  if (NotNull(audioConvert)) ::av_freep             (&audioConvert ) ;
  ////////////////////////////////////////////////////////////////////
  Frame         = NULL                                               ;
  RGB           = NULL                                               ;
  AudioFrame    = NULL                                               ;
  Captions      = NULL                                               ;
  VideoCtx      = NULL                                               ;
  AudioCtx      = NULL                                               ;
  CaptionCtx    = NULL                                               ;
  FormatCtx     = NULL                                               ;
  Dictionary    = NULL                                               ;
  VideoCodec    = NULL                                               ;
  AudioCodec    = NULL                                               ;
  CaptionCodec  = NULL                                               ;
  VideoStream   = NULL                                               ;
  AudioStream   = NULL                                               ;
  CaptionStream = NULL                                               ;
  ConvertCtx    = NULL                                               ;
  Resample      = NULL                                               ;
  audioConvert  = NULL                                               ;
  ////////////////////////////////////////////////////////////////////
  return true                                                        ;
}

void FFmpeg::Decoder::Initialize(AVPacket * packet)
{
  if (IsNull(packet        )) return ;
  ::av_init_packet ( packet )        ;
}

void FFmpeg::Decoder::Release(AVPacket * packet)
{
  if (IsNull(packet        )) return ;
  ::av_free_packet ( packet )        ;
}

bool FFmpeg::Decoder::FindStream(void)
{
  int ret                                                 ;
  if (IsNull(FormatCtx))                                  {
    Error = AVERROR_DECODER_NOT_FOUND                     ;
    return false                                          ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  ret = ::avformat_find_stream_info(FormatCtx,NULL)       ;
  if (ret<0)                                              {
    Error = ret                                           ;
    ::avformat_close_input(&FormatCtx)                    ;
    FormatCtx = NULL                                      ;
    return false                                          ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  for (int i=0;i<(int)FormatCtx->nb_streams;i++)          {
    int t = (int)FormatCtx->streams[i]->codec->codec_type ;
    switch (FormatCtx->streams[i]->codec->codec_type)     {
      case AVMEDIA_TYPE_VIDEO                             :
        if ( VideoIndex < 0 ) VideoIndex = i              ;
      break                                               ;
      case AVMEDIA_TYPE_AUDIO                             :
        if ( AudioIndex < 0 ) AudioIndex = i              ;
      break                                               ;
      case AVMEDIA_TYPE_SUBTITLE                          :
        if ( Subtitle   < 0 ) Subtitle   = i              ;
      break                                               ;
      case AVMEDIA_TYPE_DATA                              :
        DataChannel       ( i )                           ;
        Extras << t                                       ;
      break                                               ;
      case AVMEDIA_TYPE_ATTACHMENT                        :
        AttachmentChannel ( i )                           ;
        Extras << t                                       ;
      break                                               ;
      case AVMEDIA_TYPE_NB                                :
        NbChannel         ( i )                           ;
        Extras << t                                       ;
      break                                               ;
      case AVMEDIA_TYPE_UNKNOWN                           :
      default                                             :
        UnknownChannel    ( i )                           ;
        Extras << t                                       ;
      break                                               ;
    }                                                     ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  return true                                             ;
}

void FFmpeg::Decoder::DataChannel (int)
{
}

void FFmpeg::Decoder::AttachmentChannel (int)
{
}

void FFmpeg::Decoder::NbChannel (int)
{
}

void FFmpeg::Decoder::UnknownChannel (int)
{
}

bool FFmpeg::Decoder::FindVideo(void)
{
  nKickOut ( VideoIndex < 0 , false )                      ;
  VideoStream = FormatCtx->streams[VideoIndex]             ;
  VideoCtx    = FormatCtx->streams[VideoIndex]->codec      ;
  VideoCodec  = ::avcodec_find_decoder(VideoCtx->codec_id) ;
  return NotNull(VideoCodec)                               ;
}

bool FFmpeg::Decoder::FindAudio(void)
{
  nKickOut ( AudioIndex < 0 , false )                      ;
  AudioStream = FormatCtx->streams[AudioIndex]             ;
  AudioCtx    = FormatCtx->streams[AudioIndex]->codec      ;
  AudioCodec  = ::avcodec_find_decoder(AudioCtx->codec_id) ;
  return NotNull(AudioCodec)                               ;
}

bool FFmpeg::Decoder::FindCaption(void)
{
  nKickOut ( Subtitle < 0 , false )                            ;
  CaptionStream = FormatCtx->streams[Subtitle]                 ;
  CaptionCtx    = FormatCtx->streams[Subtitle]->codec          ;
  CaptionCodec  = ::avcodec_find_decoder(CaptionCtx->codec_id) ;
  return NotNull(CaptionCodec)                                 ;
}

bool FFmpeg::Decoder::OpenVideo(void)
{
  nKickOut ( VideoIndex < 0     , false )                    ;
  nKickOut ( IsNull(VideoCtx  ) , false )                    ;
  nKickOut ( IsNull(VideoCodec) , false )                    ;
  bool success = false                                       ;
  int  ret                                                   ;
  if (NotNull(Dictionary))                                   {
    ret   = ::avcodec_open2(VideoCtx,VideoCodec,&Dictionary) ;
  } else                                                     {
    ret   = ::avcodec_open2(VideoCtx,VideoCodec,NULL       ) ;
  }                                                          ;
  success = (ret>=0)                                         ;
  Error   = ret                                              ;
  isVideo = success                                          ;
  if (success)                                               {
    Frame = ::av_frame_alloc()                               ;
  }                                                          ;
  return success                                             ;
}

bool FFmpeg::Decoder::OpenAudio(void)
{
  nKickOut ( AudioIndex < 0     , false )                       ;
  nKickOut ( IsNull(AudioCtx  ) , false )                       ;
  nKickOut ( IsNull(AudioCodec) , false )                       ;
  int ret                                                       ;
  if (NotNull(Dictionary))                                      {
    ret = ::avcodec_open2(AudioCtx,AudioCodec,&Dictionary)      ;
  } else                                                        {
    ret = ::avcodec_open2(AudioCtx,AudioCodec,NULL       )      ;
  }                                                             ;
  Error   = ret                                                 ;
  isAudio = ( ret >= 0 )                                        ;
  if (isAudio)                                                  {
    bool planar    = false                                      ;
    int  av_planar = -1                                         ;
    AudioFrame = ::av_frame_alloc()                             ;
    ::av_frame_unref ( AudioFrame )                             ;
    av_planar = av_sample_fmt_is_planar(AudioCtx->sample_fmt)   ;
    planar    = ( av_planar == 1 )                              ;
    if (planar && AudioCtx->channels>1)                         {
      enum AVSampleFormat T                                     ;
      switch ( AudioCtx -> sample_fmt )                         {
        case AV_SAMPLE_FMT_U8P  : T = AV_SAMPLE_FMT_U8  ; break ;
        case AV_SAMPLE_FMT_S16P : T = AV_SAMPLE_FMT_S16 ; break ;
        case AV_SAMPLE_FMT_S32P : T = AV_SAMPLE_FMT_S32 ; break ;
        case AV_SAMPLE_FMT_FLTP : T = AV_SAMPLE_FMT_FLT ; break ;
        case AV_SAMPLE_FMT_DBLP : T = AV_SAMPLE_FMT_DBL ; break ;
      }                                                         ;
      if ( T != AudioCtx -> sample_fmt )                        {
        Resample = ::swr_alloc  (                             ) ;
        ::av_opt_set_int        (Resample,"in_channel_layout"   , AudioCtx->channel_layout,0) ;
        ::av_opt_set_int        (Resample,"out_channel_layout"  , AV_CH_LAYOUT_STEREO     ,0) ;
        ::av_opt_set_int        (Resample,"in_sample_rate"      , AudioCtx->sample_rate   ,0) ;
        ::av_opt_set_int        (Resample,"out_sample_rate"     , AudioCtx->sample_rate   ,0) ;
        ::av_opt_set_sample_fmt (Resample,"in_sample_fmt"       , AudioCtx->sample_fmt    ,0) ;
        ::av_opt_set_sample_fmt (Resample,"out_sample_fmt"      , T                       ,0) ;
        ::swr_init              (Resample                     ) ;
        ::av_samples_alloc((uint8_t**)&audioConvert,NULL,AudioCtx->channels,AudioCtx->sample_rate,T,0) ;
      }                                                         ;
    }                                                           ;
  }                                                             ;
  return isAudio                                                ;
}

bool FFmpeg::Decoder::OpenCaption(void)
{
  nKickOut ( Subtitle < 0         , false )                    ;
  nKickOut ( IsNull(CaptionCtx  ) , false )                    ;
  nKickOut ( IsNull(CaptionCodec) , false )                    ;
  int ret                                                      ;
  if (NotNull(Dictionary))                                     {
    ret = ::avcodec_open2(CaptionCtx,CaptionCodec,&Dictionary) ;
  } else                                                       {
    ret = ::avcodec_open2(CaptionCtx,CaptionCodec,NULL       ) ;
  }                                                            ;
  Error = ret                                                  ;
  if (ret>=0)                                                  {
    Captions = new AVSubtitle()                                ;
  }                                                            ;
  return ( ret >= 0 )                                          ;
}

bool FFmpeg::Decoder::AvConvertCtx(QSize size,int format,int method)
{
  nKickOut ( IsNull(VideoCtx)  , false )     ;
  RGB        = ::av_frame_alloc()            ;
  nKickOut ( IsNull(RGB)       , false )     ;
  int ret                                    ;
  ret = ::av_image_alloc                     (
          RGB->data                          ,
          RGB->linesize                      ,
          Width  ( )                         ,
          Height ( )                         ,
          (enum AVPixelFormat)format         ,
          32                               ) ;
  nKickOut ( nLess ( ret , 0 ) , false )     ;
  ConvertCtx = ::sws_getContext              (
                  VideoCtx -> width          ,
                  VideoCtx -> height         ,
                  VideoCtx -> pix_fmt        ,
                  size . width  ()           ,
                  size . height ()           ,
                  (enum AVPixelFormat)format ,
                  method                     ,
                  NULL                       ,
                  NULL                       ,
                  NULL                     ) ;
  return NotNull(ConvertCtx)                 ;
}

int FFmpeg::Decoder::Frames(void)
{
  nKickOut ( IsNull(VideoStream) , 0 ) ;
  return (int)VideoStream->nb_frames   ;
}

long long FFmpeg::Decoder::Duration(void)
{
  nKickOut ( IsNull(FormatCtx) , 0 ) ;
  return FormatCtx->duration         ;
}

long long FFmpeg::Decoder::Timestamp(AVPacket & Packet)
{
  nKickOut ( IsNull(FormatCtx) , 0 )            ;
  long long timestamp = AV_NOPTS_VALUE          ;
  if (Packet.stream_index==VideoIndex)          {
    long long pts = Packet.pts                  ;
    if (NoPTS(pts))                             {
      long long dts = Packet.dts                ;
      if (HasPTS(dts))                          {
        timestamp  = dts                        ;
        timestamp *= AV_TIME_BASE               ;
        timestamp *= VideoStream->time_base.num ;
        timestamp /= VideoStream->time_base.den ;
      }                                         ;
    } else                                      {
      timestamp  = pts                          ;
      timestamp *= AV_TIME_BASE                 ;
      timestamp *= VideoStream->time_base.num   ;
      timestamp /= VideoStream->time_base.den   ;
    }                                           ;
  } else
  if (Packet.stream_index==AudioIndex)          {
    long long pts = Packet.pts                  ;
    if (NoPTS(pts))                             {
      long long dts = Packet.dts                ;
      if (HasPTS(dts))                          {
        timestamp  = dts                        ;
        timestamp *= AV_TIME_BASE               ;
        timestamp *= AudioStream->time_base.num ;
        timestamp /= AudioStream->time_base.den ;
      }                                         ;
    } else                                      {
      timestamp  = pts                          ;
      timestamp *= AV_TIME_BASE                 ;
      timestamp *= AudioStream->time_base.num   ;
      timestamp /= AudioStream->time_base.den   ;
    }                                           ;
  }                                             ;
  return timestamp                              ;
}

double FFmpeg::Decoder::VideoRate(void)
{
  nKickOut      ( IsNull(VideoStream) , 0 ) ;
  return av_q2d ( VideoStream->time_base  ) ;
}

double FFmpeg::Decoder::AudioRate(void)
{
  nKickOut      ( IsNull(AudioStream) , 0 ) ;
  return av_q2d ( AudioStream->time_base  ) ;
}

int FFmpeg::Decoder::ReadPacket(AVPacket & Packet)
{
  nKickOut               ( IsNull(FormatCtx) , AVERROR_INVALIDDATA ) ;
  return ::av_read_frame ( FormatCtx         , &Packet             ) ;
}

bool FFmpeg::Decoder::isVideoChannel(AVPacket & Packet)
{
  nKickOut ( VideoIndex < 0 , false            ) ;
  return   ( Packet.stream_index == VideoIndex ) ;
}

bool FFmpeg::Decoder::isAudioChannel(AVPacket & Packet)
{
  nKickOut ( AudioIndex < 0 , false            ) ;
  return   ( Packet.stream_index == AudioIndex ) ;
}

bool FFmpeg::Decoder::isSubtitle(AVPacket & Packet)
{
  nKickOut ( Subtitle < 0 , false            ) ;
  return   ( Packet.stream_index == Subtitle ) ;
}

long long FFmpeg::Decoder::PTS(AVPacket & Packet)
{
  return Packet . pts ;
}

long long FFmpeg::Decoder::DTS(AVPacket & Packet)
{
  return Packet . dts ;
}

bool FFmpeg::Decoder::NoPTS (long long pts)
{
  return ( pts == AV_NOPTS_VALUE ) ;
}

bool FFmpeg::Decoder::HasPTS (long long pts)
{
  return ( pts != AV_NOPTS_VALUE ) ;
}

AVFrame * FFmpeg::Decoder::AllocateFrame (void)
{
  return ::av_frame_alloc ( ) ;
}

int FFmpeg::Decoder::AudioPacketSize (int bufferSize)
{
  return ( bufferSize + FF_INPUT_BUFFER_PADDING_SIZE ) ;
}

int FFmpeg::Decoder::AvSampleFormat (void)
{
  nKickOut ( IsNull(AudioCtx) , 0 ) ;
  return AudioCtx -> sample_fmt     ;
}

int FFmpeg::Decoder::AvSampleRate (void)
{
  nKickOut ( IsNull(AudioCtx) , 0 ) ;
  return AudioCtx -> sample_rate    ;
}

int FFmpeg::Decoder::AvBits(void)
{
  nKickOut ( IsNull(AudioCtx) , 0 )     ;
  switch (AudioCtx -> sample_fmt)       {
    case AV_SAMPLE_FMT_U8   : return  8 ;
    case AV_SAMPLE_FMT_S16  : return 16 ;
    case AV_SAMPLE_FMT_S32  : return 32 ;
    case AV_SAMPLE_FMT_FLT  : return 32 ;
    case AV_SAMPLE_FMT_DBL  : return 64 ;
    case AV_SAMPLE_FMT_U8P  : return  8 ;
    case AV_SAMPLE_FMT_S16P : return 16 ;
    case AV_SAMPLE_FMT_S32P : return 32 ;
    case AV_SAMPLE_FMT_FLTP : return 32 ;
    case AV_SAMPLE_FMT_DBLP : return 64 ;
    case AV_SAMPLE_FMT_NONE             :
    case AV_SAMPLE_FMT_NB               :
    break                               ;
  }                                     ;
  return 0                              ;
}

bool FFmpeg::Decoder::AvFloat(void)
{
  nKickOut ( IsNull(AudioCtx) , false )    ;
  switch (AudioCtx -> sample_fmt)          {
    case AV_SAMPLE_FMT_U8   : return false ;
    case AV_SAMPLE_FMT_S16  : return false ;
    case AV_SAMPLE_FMT_S32  : return false ;
    case AV_SAMPLE_FMT_FLT  : return true  ;
    case AV_SAMPLE_FMT_DBL  : return true  ;
    case AV_SAMPLE_FMT_NONE : return false ;
    case AV_SAMPLE_FMT_U8P  : return false ;
    case AV_SAMPLE_FMT_S16P : return false ;
    case AV_SAMPLE_FMT_S32P : return false ;
    case AV_SAMPLE_FMT_FLTP : return true  ;
    case AV_SAMPLE_FMT_DBLP : return true  ;
    case AV_SAMPLE_FMT_NB                  :
    break                                  ;
  }                                        ;
  return false                             ;
}

int FFmpeg::Decoder::Channels (void)
{
  nKickOut ( IsNull(AudioCtx) , 0 ) ;
  return AudioCtx -> channels       ;
}

int FFmpeg::Decoder::BitRate (void)
{
  nKickOut ( IsNull(AudioCtx) , 0 ) ;
  return AudioCtx -> bit_rate       ;
}

int FFmpeg::Decoder::Width(void)
{
  nKickOut ( IsNull(VideoCtx) , 0 ) ;
  return VideoCtx -> width          ;
}

int FFmpeg::Decoder::Height(void)
{
  nKickOut ( IsNull(VideoCtx) , 0 ) ;
  return VideoCtx -> height         ;
}

QString FFmpeg::Decoder::VideoCodecName(void)
{
  nKickOut       ( IsNull(VideoCodec) , "" ) ;
  return QString ( VideoCodec -> long_name ) ;
}

QString FFmpeg::Decoder::AudioCodecName(void)
{
  nKickOut       ( IsNull(AudioCodec) , "" ) ;
  return QString ( AudioCodec -> long_name ) ;
}

int FFmpeg::Decoder::BytesPerFrame(void)
{
  nKickOut ( IsNull(AudioCtx) , 0 )             ;
  int channels = AudioCtx -> channels           ;
  int bytes    = 0                              ;
  switch ( AudioCtx -> sample_fmt )             {
    case AV_SAMPLE_FMT_U8   : bytes = 1 ; break ;
    case AV_SAMPLE_FMT_S16  : bytes = 2 ; break ;
    case AV_SAMPLE_FMT_S32  : bytes = 4 ; break ;
    case AV_SAMPLE_FMT_FLT  : bytes = 4 ; break ;
    case AV_SAMPLE_FMT_DBL  : bytes = 8 ; break ;
    case AV_SAMPLE_FMT_U8P  : bytes = 1 ; break ;
    case AV_SAMPLE_FMT_S16P : bytes = 2 ; break ;
    case AV_SAMPLE_FMT_S32P : bytes = 4 ; break ;
    case AV_SAMPLE_FMT_FLTP : bytes = 4 ; break ;
    case AV_SAMPLE_FMT_DBLP : bytes = 8 ; break ;
    case AV_SAMPLE_FMT_NONE                     :
    case AV_SAMPLE_FMT_NB                       :
    return 0                                    ;
  }                                             ;
  return bytes * channels                       ;
}

long long FFmpeg::Decoder::AudioBufferSize(int milliseconds)
{
  nKickOut ( IsNull(AudioCtx) , 0 )             ;
  int channels = AudioCtx -> channels           ;
  int rate     = AudioCtx -> sample_rate        ;
  int bytes    = 0                              ;
  switch ( AudioCtx -> sample_fmt )             {
    case AV_SAMPLE_FMT_U8   : bytes = 1 ; break ;
    case AV_SAMPLE_FMT_S16  : bytes = 2 ; break ;
    case AV_SAMPLE_FMT_S32  : bytes = 4 ; break ;
    case AV_SAMPLE_FMT_FLT  : bytes = 4 ; break ;
    case AV_SAMPLE_FMT_DBL  : bytes = 8 ; break ;
    case AV_SAMPLE_FMT_U8P  : bytes = 1 ; break ;
    case AV_SAMPLE_FMT_S16P : bytes = 2 ; break ;
    case AV_SAMPLE_FMT_S32P : bytes = 4 ; break ;
    case AV_SAMPLE_FMT_FLTP : bytes = 4 ; break ;
    case AV_SAMPLE_FMT_DBLP : bytes = 8 ; break ;
    case AV_SAMPLE_FMT_NONE                     :
    case AV_SAMPLE_FMT_NB                       :
    return 0                                    ;
  }                                             ;
  ///////////////////////////////////////////////
  long long s = bytes                           ;
  s *= channels                                 ;
  s *= rate                                     ;
  s *= milliseconds                             ;
  s /= 1000                                     ;
  return s                                      ;
}

int FFmpeg::Decoder::DecodeAudio(AVPacket & Packet,unsigned char * data)
{
  nKickOut ( !isAudio , 0 )                        ;
  //////////////////////////////////////////////////
  unsigned char * dp       = NULL                  ;
  int             audiolen = 0                     ;
  int             len      = 0                     ;
  int             dataSize = 0                     ;
  int             gotFrame = 0                     ;
  //////////////////////////////////////////////////
  av_frame_unref(AudioFrame)                       ;
  while ( nGreater ( Packet.size , 0 ) )           {
    gotFrame = 0                                   ;
    len      = ::avcodec_decode_audio4             (
                 AudioCtx                          ,
                 AudioFrame                        ,
                 &gotFrame                         ,
                 &Packet                         ) ;
    if (len < 0) return audiolen                   ;
    if ( nGreater ( gotFrame , 0 ) )               {
      dp      = &data[audiolen]                    ;
      dataSize = ::av_samples_get_buffer_size      (
                   NULL                            ,
                   AudioCtx   -> channels          ,
                   AudioFrame -> nb_samples        ,
                   AudioCtx   -> sample_fmt        ,
                   1                             ) ;
      if (dataSize>0)                              {
        char * src = (char *)AudioFrame->data[0]   ;
        if (NotNull(Resample))                     {
          ::swr_convert(Resample                   ,
                        &audioConvert              ,
                        AudioFrame -> nb_samples   ,
      (const uint8_t **)AudioFrame -> data         ,
                        AudioFrame -> nb_samples ) ;
          src = (char *)audioConvert               ;
        }                                          ;
        memcpy(dp,src,dataSize)                    ;
        audiolen += dataSize                       ;
        return audiolen                            ;
      }                                            ;
    }                                              ;
    Packet.size -= len                             ;
    Packet.data += len                             ;
    Packet.pts   = AV_NOPTS_VALUE                  ;
    Packet.dts   = AV_NOPTS_VALUE                  ;
  }                                                ;
  return audiolen                                  ;
}

bool FFmpeg::Decoder::DecodeImage(AVPacket & Packet,int & gotFrame)
{
  nKickOut ( !isVideo , false )          ;
  ////////////////////////////////////////
  int len  = 0                           ;
  gotFrame = 0                           ;
  while ( nGreater ( Packet.size , 0 ) ) {
    len = ::avcodec_decode_video2        (
            VideoCtx                     ,
            Frame                        ,
            &gotFrame                    ,
            &Packet                    ) ;
    if (len      <  0) return false      ;
    Packet.size -= len                   ;
    Packet.data += len                   ;
    if (gotFrame >  0) return true       ;
  }                                      ;
  ////////////////////////////////////////
  return true                            ;
}

bool FFmpeg::Decoder::CopyImage (int format)
{
  nKickOut ( IsNull(RGB) , false )  ;
  ::av_image_copy                   (
    RGB      -> data                ,
    RGB      -> linesize            ,
    (const uint8_t **)Frame -> data ,
    Frame    -> linesize            ,
    (enum AVPixelFormat)format      ,
    VideoCtx -> width               ,
    VideoCtx -> height            ) ;
  return true                       ;
}

bool FFmpeg::Decoder::ScaleImage (QSize size)
{
  nKickOut ( IsNull(RGB       ) , false ) ;
  nKickOut ( IsNull(ConvertCtx) , false ) ;
  int h                                   ;
  h = ::sws_scale                         (
        ConvertCtx                        ,
        Frame -> data                     ,
        Frame -> linesize                 ,
        0                                 ,
        size   . height()                 ,
        RGB   -> data                     ,
        RGB   -> linesize               ) ;
  return ( h == size.height() )           ;
}

bool FFmpeg::Decoder::DecodeCaption (AVPacket & Packet)
{
  AVPacket * avPacket = &Packet               ;
  if (IsNull(CaptionCtx  )) return false      ;
  if (IsNull(CaptionCodec)) return false      ;
  if (IsNull(Captions    )) return false      ;
  /////////////////////////////////////////////
  int ret      = 0                            ;
  int gotFrame = 0                            ;
  ret = ::avcodec_decode_subtitle2            (
        CaptionCtx                            ,
        Captions                              ,
        &gotFrame                             ,
        avPacket                            ) ;
  /////////////////////////////////////////////
  nKickOut ( nLess ( ret      , 0 ) , false ) ;
  nKickOut ( nLess ( gotFrame , 1 ) , false ) ;
  /////////////////////////////////////////////
  return true                                 ;
}

bool FFmpeg::Decoder::RawSeek (long long msecs)
{
  int rt                   ;
  rt = ::av_seek_frame     (
         FormatCtx         ,
         -1                ,
         msecs * 1000      ,
         AVSEEK_FLAG_ANY ) ;
  //////////////////////////
  return ( rt >= 0 )       ;
}
