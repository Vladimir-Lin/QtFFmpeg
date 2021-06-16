#include "qtffmpeg.h"

#pragma message("QtFFmpeg encoder requires a massive rewrite")

#define IsNull(item)                  (NULL==(item))
#define NotNull(item)                 (NULL!=(item))
#define nDropOut(Condition)           if (Condition) return
#define nKickOut(Condition,Result)    if (Condition) return (Result)
#define nGreater(A,B)                 ((A)>(B))
#define nLess(A,B)                    ((A)<(B))

FFmpeg::Encoder:: Encoder  ( void             )
                : Filename ( ""               )
                , encoder  ( NULL             )
                , resample ( NULL             )
                , buffer   ( NULL             )
                , sample   ( NULL             )
                , codec    ( AV_CODEC_ID_NONE )
{
}

FFmpeg::Encoder::~Encoder(void)
{
}

bool FFmpeg::Encoder::exists(int codecId,int DeviceType)
{
  AVCodec * codec = NULL                                  ;
  codec = ::avcodec_find_encoder((enum AVCodecID)codecId) ;
  nKickOut ( IsNull(codec)             , false )          ;
  nKickOut ( codec->type != DeviceType , false )          ;
  return true                                             ;
}

bool FFmpeg::Encoder::OpenAudio(int c,int rate,int channels,int format)
{
  codec   = c                                                ;
  encoder = ::avcodec_find_encoder((enum AVCodecID)codec)    ;
  if (IsNull(encoder)) return false                          ;
  ////////////////////////////////////////////////////////////
  resample               = NULL                              ;
  SourceRate             = rate                              ;
  SourceChannels         = channels                          ;
  SourceFormat           = (AVSampleFormat)format            ;
  TargetRate             = rate                              ;
  TargetChannels         = channels                          ;
  TargetFormat           = (AVSampleFormat)format            ;
  context                = ::avcodec_alloc_context3(encoder) ;
  context -> sample_rate = rate                              ;
  context -> channels    = channels                          ;
  context -> sample_fmt  = (AVSampleFormat)format            ;
  ////////////////////////////////////////////////////////////
  if (::avcodec_open2(context,encoder,NULL)<0)               {
    ::avcodec_close ( context )                              ;
    return false                                             ;
  }                                                          ;
  if (context->frame_size<=0)                                {
    ::avcodec_close ( context )                              ;
    return false                                             ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  BytesPerFrame  = channels                                  ;
  int bytes = 0                                              ;
  switch (format)                                            {
    case AV_SAMPLE_FMT_U8   : bytes = 1 ; break              ;
    case AV_SAMPLE_FMT_S16  : bytes = 2 ; break              ;
    case AV_SAMPLE_FMT_S32  : bytes = 4 ; break              ;
    case AV_SAMPLE_FMT_FLT  : bytes = 4 ; break              ;
    case AV_SAMPLE_FMT_DBL  : bytes = 8 ; break              ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  BytesPerFrame *= bytes                                     ;
  if ( BytesPerFrame <= 0 )                                  {
    ::avcodec_close ( context )                              ;
    return false                                             ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  int BPF = BytesPerFrame                                    ;
  TargetPerFrame = BPF                                       ;
  BPF *= context -> frame_size                               ;
  BPF *= 16                                                  ;
  buffer = new unsigned char [ BPF ]                         ;
  sample = new unsigned char [ BPF ]                         ;
  return NotNull(encoder)                                    ;
}

bool FFmpeg::Encoder::setOutput(int rate,int channels,int format)
{
  TargetRate     = rate                                   ;
  TargetChannels = channels                               ;
  TargetFormat   = (AVSampleFormat)format                 ;
  bool resampling = false                                 ;
  if (TargetRate    !=SourceRate    ) resampling = true   ;
  if (TargetChannels!=SourceChannels) resampling = true   ;
  if (TargetFormat  !=SourceFormat  ) resampling = true   ;
  if (!resampling) return true                            ;
  ::avcodec_close ( context )                             ;
  encoder = ::avcodec_find_encoder((enum AVCodecID)codec) ;
  context = ::avcodec_alloc_context3(encoder)             ;
  context -> sample_rate = rate                           ;
  context -> channels    = channels                       ;
  context -> sample_fmt  = (AVSampleFormat)format         ;
  if (::avcodec_open2(context,encoder,NULL)<0)            {
    ::avcodec_close ( context )                           ;
    return false                                          ;
  }                                                       ;
  if (context->frame_size<=0)                             {
    ::avcodec_close ( context )                           ;
    return false                                          ;
  }                                                       ;
  resample = ::av_audio_resample_init                     (
              TargetChannels                              ,
              SourceChannels                              ,
              TargetRate                                  ,
              SourceRate                                  ,
              (enum AVSampleFormat)TargetFormat           ,
              (enum AVSampleFormat)SourceFormat           ,
              0,0,0,0                                   ) ;
  TargetPerFrame  = channels                              ;
  int bytes = 0                                           ;
  switch (format)                                         {
    case AV_SAMPLE_FMT_U8   : bytes = 1 ; break           ;
    case AV_SAMPLE_FMT_S16  : bytes = 2 ; break           ;
    case AV_SAMPLE_FMT_S32  : bytes = 4 ; break           ;
    case AV_SAMPLE_FMT_FLT  : bytes = 4 ; break           ;
    case AV_SAMPLE_FMT_DBL  : bytes = 8 ; break           ;
  }                                                       ;
  TargetPerFrame *= bytes                                 ;
  return true                                             ;
}

bool FFmpeg::Encoder::Compatible(void)
{
  switch (encoder->id)                                         {
    case AV_CODEC_ID_MP3                                       :
      if (TargetFormat==(int)AV_SAMPLE_FMT_U8)                 {
        setOutput(TargetRate,TargetChannels,AV_SAMPLE_FMT_S16) ;
      } else
      if (TargetFormat==(int)AV_SAMPLE_FMT_DBL)                {
        setOutput(TargetRate,TargetChannels,AV_SAMPLE_FMT_FLT) ;
      }                                                        ;
    break                                                      ;
    default                                                    :
    return false                                               ;
  }                                                            ;
  return true                                                  ;
}

void FFmpeg::Encoder::Resampling(int frames)
{
  int bucket = ::audio_resample (
    resample                    ,
    (short *)buffer             ,
    (short *)sample             ,
    frames                    ) ;
  bucket  *= TargetPerFrame     ;
  memcpy(sample,buffer,bucket)  ;
}

bool FFmpeg::Encoder::Close(void)
{
  if (NotNull(resample))                  {
    ::audio_resample_close(resample)      ;
  }                                       ;
  if (NotNull(buffer  )) delete [] buffer ;
  if (NotNull(sample  )) delete [] sample ;
  buffer = NULL                           ;
  sample = NULL                           ;
  ::avcodec_close ( context )             ;
  encoder = NULL                          ;
  return true                             ;
}

int FFmpeg::Encoder::FrameSize(void)
{
  return context -> frame_size ;
}

int FFmpeg::Encoder::Collect(unsigned char * data,int length,int compressed)
{
  int rest = length - compressed      ;
  memcpy(data,&data[compressed],rest) ;
  return rest                         ;
}

int FFmpeg::Encoder::Encode(QIODevice & IO,int length,unsigned char * data,bool flush)
{
  nKickOut ( length < 0         , 0 )                 ;
  nKickOut ( IsNull ( encoder ) , 0 )                 ;
  nKickOut ( IsNull ( context ) , 0 )                 ;
  int  compressed = 0                                 ;
  int  fs         = context -> frame_size             ;
  int  fb         = this    -> BytesPerFrame * fs     ;
  int  rest       = length                            ;
  int  index      = 0                                 ;
  int  mpr        = 0                                 ;
  bool written    = true                              ;
  if (fb>length) written = false                      ;
  if (flush    ) written = true                       ;
  while (written)                                     {
    if (rest<=0) written = false ;                 else
    if (fb>rest)                                      {
      if (flush)                                      {
        memset(sample,0           ,fb  )              ;
        memcpy(sample,&data[index],rest)              ;
        addLength ( rest )                            ;
        rest       = 0                                ;
        index      = length                           ;
        compressed = length                           ;
      } else                                          {
        written = false                               ;
      }                                               ;
    } else                                            {
      memcpy(sample,&data[index],fb)                  ;
      rest       -= fb                                ;
      index      += fb                                ;
      compressed += fb                                ;
      addLength ( fb )                                ;
    }                                                 ;
    if (written)                                      {
      if (NotNull(resample)) Resampling(fs)           ;
#pragma message("avcodec_encode_audio required to change to avcodec_encode_audio2")
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
      int avcodec_encode_audio2(AVCodecContext *avctx, AVPacket *avpkt,
                                const AVFrame *frame, int *got_packet_ptr);

      mpr = ::avcodec_encode_audio2                   (
              context                                 ,
              (uint8_t*)buffer                        ,
              fs                                      ,
              (short*)sample                        ) ;
#endif
      if (mpr>0)                                      {
        IO.write((const char *)buffer,mpr)            ;
        addCompressed ( mpr )                         ;
      }                                               ;
    }                                                 ;
  }                                                   ;
  return compressed                                   ;
}

void FFmpeg::Encoder::addLength(int length)
{ Q_UNUSED ( length ) ;
}

void FFmpeg::Encoder::addCompressed(int length)
{ Q_UNUSED ( length ) ;
}
