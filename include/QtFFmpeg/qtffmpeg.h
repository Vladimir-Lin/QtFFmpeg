/****************************************************************************
 *
 * Copyright (C) 2015 Neutrino International Inc.
 *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin
 *
 * QtFFmpeg acts as an interface between Qt and FFmpeg library.
 * Please keep QtFFmpeg as simple as possible.
 *
 ****************************************************************************/

#ifndef QT_FFMPEG_H
#define QT_FFMPEG_H

#include <QtCore>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <sys/types.h>
#ifdef Q_OS_ANDROID
#define __STDC_CONSTANT_MACROS
 #ifdef _STDINT_H
  #undef _STDINT_H
 #endif
#endif
#include <stdint.h>
#if defined(Q_OS_IOS)
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#elif defined(Q_OS_ANDROID)
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#elif defined(Q_OS_LINUX)
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#elif defined(Q_OS_MACX)
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#else
#include <varargs.h>
#endif
#if   defined(Q_OS_ANDROID)
#include <limits.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>
#include <fcntl.h>
#elif defined(Q_OS_IOS)
#include <limits.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>
#include <fcntl.h>
#elif defined(Q_OS_LINUX)
#include <limits.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>
#include <fcntl.h>
#elif defined(Q_OS_MACX)
#include <limits.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>
#include <fcntl.h>
#else
#include <process.h>
#include <windows.h>
#endif
#ifdef Q_OS_WIN
#include <omp.h>
#else
#include <openmp.h>
#endif
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/avcodec.h>
#include <libavcodec/avfft.h>
#include <libavcodec/dv_profile.h>
#include <libavcodec/dxva2.h>
#include <libavcodec/vaapi.h>
#include <libavcodec/vorbis_parser.h>
#include <libavutil/avutil.h>
#include <libavutil/adler32.h>
#include <libavutil/aes.h>
#include <libavutil/attributes.h>
#include <libavutil/audio_fifo.h>
#include <libavutil/avassert.h>
#include <libavutil/avconfig.h>
#include <libavutil/avstring.h>
#include <libavutil/base64.h>
#include <libavutil/blowfish.h>
#include <libavutil/bprint.h>
#include <libavutil/bswap.h>
#include <libavutil/buffer.h>
#include <libavutil/camellia.h>
#include <libavutil/cast5.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/cpu.h>
#include <libavutil/crc.h>
#include <libavutil/dict.h>
#include <libavutil/display.h>
#include <libavutil/downmix_info.h>
#include <libavutil/error.h>
#include <libavutil/eval.h>
#include <libavutil/ffversion.h>
#include <libavutil/fifo.h>
#include <libavutil/file.h>
#include <libavutil/frame.h>
#include <libavutil/hash.h>
#include <libavutil/hmac.h>
#include <libavutil/imgutils.h>
#include <libavutil/intfloat.h>
#include <libavutil/intreadwrite.h>
#include <libavutil/lfg.h>
#include <libavutil/log.h>
#include <libavutil/lzo.h>
#include <libavutil/macros.h>
#include <libavutil/mathematics.h>
#include <libavutil/md5.h>
#include <libavutil/mem.h>
#include <libavutil/motion_vector.h>
#include <libavutil/murmur3.h>
#include <libavutil/opt.h>
#include <libavutil/parseutils.h>
#include <libavutil/pixdesc.h>
#include <libavutil/pixelutils.h>
#include <libavutil/pixfmt.h>
#include <libavutil/random_seed.h>
#include <libavutil/rational.h>
#include <libavutil/replaygain.h>
#include <libavutil/ripemd.h>
#include <libavutil/samplefmt.h>
#include <libavutil/sha.h>
#include <libavutil/sha512.h>
#include <libavutil/stereo3d.h>
#include <libavutil/threadmessage.h>
#include <libavutil/time.h>
#include <libavutil/twofish.h>
#include <libavutil/xtea.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavfilter/buffersrc.h>
#include <libavfilter/buffersink.h>
#include <libswresample/swresample.h>
#include <libpostproc/postprocess.h>
#include <libswscale/swscale.h>
}

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#  if defined(QT_BUILD_QTFFMPEG_LIB)
#    define Q_FFMPEG_EXPORT Q_DECL_EXPORT
#  else
#    define Q_FFMPEG_EXPORT Q_DECL_IMPORT
#  endif
#else
#    define Q_FFMPEG_EXPORT
#endif

namespace FFmpeg
{

class Q_FFMPEG_EXPORT CPU         ;
class Q_FFMPEG_EXPORT Rational    ;
class Q_FFMPEG_EXPORT ScaleVector ;
class Q_FFMPEG_EXPORT ScaleFilter ;
class Q_FFMPEG_EXPORT Scaler      ;
class Q_FFMPEG_EXPORT Resampler   ;
class Q_FFMPEG_EXPORT Process     ;
class Q_FFMPEG_EXPORT Decoder     ;
class Q_FFMPEG_EXPORT Encoder     ;

Q_FFMPEG_EXPORT QStringList AudioExtensions (void) ;
Q_FFMPEG_EXPORT QStringList VideoExtensions (void) ;

class Q_FFMPEG_EXPORT CPU
{
  public:

    explicit    CPU        (void) ;
                CPU        (const CPU & cpu) ;
    virtual    ~CPU        (void) ;

    static int  Processors (void) ;
    static int  Flags      (void) ;
    static void setFlags   (int flags) ;
    static int  Parse      (unsigned int & flags,const char * string) ;
    static int  Parse      (unsigned int & flags,QString string) ;

  protected:

  private:

} ;

class Q_FFMPEG_EXPORT Rational
{
  public:

    int numerator   ;
    int denominator ;

    explicit   Rational    (void) ;
    explicit   Rational    (int numerator,int denominator) ;
               Rational    (const Rational   & r) ;
               Rational    (const AVRational & r) ;
               Rational    (      AVRational * r) ;
    virtual   ~Rational    (void) ;

    operator   double ( )  { if ( 0 == denominator ) return 0  ;
                              return ( (double) numerator   )   /
                                     ( (double) denominator ) ; }

    AVRational To          (void) ;
    void       To          (AVRational & av) ;

    int        compare     (Rational   & av) ;
    int        compare     (AVRational & av) ;

    /*! reduce fraction */
    bool       reduce      (int64_t maxv = INT_MAX) ;

    Rational & operator *= (Rational   & av) ;
    Rational & operator *= (AVRational & av) ;
    Rational & operator /= (Rational   & av) ;
    Rational & operator /= (AVRational & av) ;
    Rational & operator += (Rational   & av) ;
    Rational & operator += (AVRational & av) ;
    Rational & operator -= (Rational   & av) ;
    Rational & operator -= (AVRational & av) ;

    void       Invert      (void) ;
    Rational   Inversion   (void) ;

    Rational & FromDouble  (double d,int maxv = INT_MAX) ;
    Rational & operator =  (double d) ;

    int        Nearer      (Rational   & q1,Rational   & q2) ;
    int        Nearer      (AVRational & q1,AVRational & q2) ;
    int        Nearest     (const AVRational * q_list) ;

    quint32    ieeeFloat   (void) ;

  protected:

  private:

} ;

class Q_FFMPEG_EXPORT ScaleVector
{
  public:

    SwsVector * vector ;

    explicit      ScaleVector (void) ;
                  ScaleVector (int length) ;
                  ScaleVector (const ScaleVector & vector) ;
                  ScaleVector (SwsVector * vector) ;
    virtual      ~ScaleVector (void) ;

    void          Clear       (void) ;
    bool          isNull      (void) ;
    ScaleVector & Allocate    (int length) ;

    ScaleVector & Constant    (double c,int length) ;
    ScaleVector & Gaussian    (double variance,double quality) ;
    ScaleVector & Identity    (void) ;

    ScaleVector & Scale       (double scalar) ;
    ScaleVector & Normalize   (double height) ;
    ScaleVector & Shift       (int    shift ) ;

    ScaleVector & Conv        (ScaleVector & vector) ;
    ScaleVector & Add         (ScaleVector & vector) ;
    ScaleVector & Subtract    (ScaleVector & vector) ;

    ScaleVector & operator += (ScaleVector & vector) ;
    ScaleVector & operator -= (ScaleVector & vector) ;

    ScaleVector & operator  = (ScaleVector & vector) ;

  protected:

  private:

} ;

class Q_FFMPEG_EXPORT ScaleFilter
{
  public:

    SwsFilter * filter ;

    explicit      ScaleFilter (void) ;
                  ScaleFilter (SwsFilter * filter) ;
                  ScaleFilter (float lumaGBlur     ,
                               float chromaGBlur   ,
                               float lumaSharpen   ,
                               float chromaSharpen ,
                               float chromaHShift  ,
                               float chromaVShift  ,
                               int   verbose     ) ;
    virtual      ~ScaleFilter (void) ;

    void          Clear       (void) ;
    bool          isNull      (void) ;
    ScaleFilter & Allocate    (float lumaGBlur     ,
                               float chromaGBlur   ,
                               float lumaSharpen   ,
                               float chromaSharpen ,
                               float chromaHShift  ,
                               float chromaVShift  ,
                               int   verbose     ) ;

  protected:

  private:

} ;

/*!
 * libswscale wrapper
 *
 */
class Q_FFMPEG_EXPORT Scaler
{
  public:

    SwsContext * scaler ;

    explicit       Scaler            (void) ;
                   Scaler            (SwsContext * scaler) ;
                   Scaler            (ScaleFilter & src,ScaleFilter & dest) ;
    virtual       ~Scaler            (void) ;

    static QString Version           (void) ;
    static const AVClass * getClass  (void) ;
    static bool    isInput           (enum AVPixelFormat pixfmt) ;
    static bool    isOutput          (enum AVPixelFormat pixfmt) ;
    static bool    isEndianness      (enum AVPixelFormat pixfmt) ;
    static void    PaletteToPacked24 (const uint8_t * src        ,
                                            uint8_t * dst        ,
                                      int             num_pixels ,
                                      const uint8_t * palette  ) ;
    static void    PaletteToPacked32 (const uint8_t * src        ,
                                            uint8_t * dst        ,
                                      int             num_pixels ,
                                      const uint8_t * palette  ) ;

    void           Clear             (void) ;
    bool           isNull            (void) ;
    Scaler &       Allocate          (void) ;

    Scaler &       Initialize        (void) ;
    Scaler &       Initialize        (ScaleFilter & src,ScaleFilter & dest) ;
    Scaler &       Get               (int                srcW      ,
                                      int                srcH      ,
                                      enum AVPixelFormat srcFormat ,
                                      int                dstW      ,
                                      int                dstH      ,
                                      enum AVPixelFormat dstFormat ,
                                      int                flags   ) ;
    Scaler &       Get               (int                srcW      ,
                                      int                srcH      ,
                                      enum AVPixelFormat srcFormat ,
                                      int                dstW      ,
                                      int                dstH      ,
                                      enum AVPixelFormat dstFormat ,
                                      int                flags     ,
                                      ScaleFilter      & srcFilter ,
                                      ScaleFilter      & dstFilter ,
                                      const double     * param   ) ;
    Scaler &       GetCached         (int                srcW      ,
                                      int                srcH      ,
                                      enum AVPixelFormat srcFormat ,
                                      int                dstW      ,
                                      int                dstH      ,
                                      enum AVPixelFormat dstFormat ,
                                      int                flags   ) ;
    Scaler &       GetCached         (int                srcW      ,
                                      int                srcH      ,
                                      enum AVPixelFormat srcFormat ,
                                      int                dstW      ,
                                      int                dstH      ,
                                      enum AVPixelFormat dstFormat ,
                                      int                flags     ,
                                      ScaleFilter      & srcFilter ,
                                      ScaleFilter      & dstFilter ,
                                      const double     * param   ) ;
    int            Scale             (const uint8_t * const srcSlice  [ ]   ,
                                      const int             srcStride [ ]   ,
                                      int                   srcSliceY       ,
                                      int                   srcSliceH       ,
                                      uint8_t       * const dst       [ ]   ,
                                      const int             dstStride [ ] ) ;
    int            setColorspace     (const int inv_table[4] ,
                                      int       srcRange     ,
                                      const int table    [4] ,
                                      int       dstRange     ,
                                      int       brightness   ,
                                      int       contrast     ,
                                      int       saturation ) ;
    int            getColorspace     (int    ** inv_table    ,
                                      int    *  srcRange     ,
                                      int    ** table        ,
                                      int    *  dstRange     ,
                                      int    *  brightness   ,
                                      int    *  contrast     ,
                                      int    *  saturation ) ;

  protected:

  private:

} ;

/*!
 * libswresample wrapper
 *
 */
class Resampler
{
  public:

    SwrContext * resampler ;

    explicit               Resampler         (void) ;
    virtual               ~Resampler         (void) ;

    static QString         Version           (void) ;
    static const AVClass * getClass          (void) ;

    void                   Clear             (void) ;
    bool                   isNull            (void) ;
    Resampler            & Allocate          (void) ;

    virtual int            Initialize        (void) ;
    virtual bool           isInitialize      (void) ;
    virtual void           Close             (void) ;

    virtual bool           setOpts           (qint64              out_ch_layout   ,
                                              enum AVSampleFormat out_sample_fmt  ,
                                              int                 out_sample_rate ,
                                              qint64              in_ch_layout    ,
                                              enum AVSampleFormat in_sample_fmt   ,
                                              int                 in_sample_rate  ,
                                              int                 log_offset      ,
                                              void              * log_ctx = NULL) ;

    virtual int            Convert           (      uint8_t ** out        ,
                                                    int        out_count  ,
                                              const uint8_t ** in         ,
                                                    int        in_count ) ;
    virtual qint64         NextPTS           (qint64 pts) ;
    virtual int            setCompensation   (int sample_delta            ,
                                              int compensation_distance ) ;
    virtual int            setChannelMapping (const int * channel_map) ;
    virtual int            setMatrix         (const double * matrix,int stride) ;
    virtual int            dropOutput        (int count) ;
    virtual int            InjectSilence     (int count) ;
    virtual qint64         getDelay          (qint64 base) ;
    virtual int            getOutSamples     (int in_samples) ;
    virtual int            ConvertFrame      (AVFrame       & output  ,
                                              AVFrame       & input ) ;
    virtual int            ConvertFrame      (      AVFrame * output  ,
                                              const AVFrame * input ) ;
    virtual int            ConfigFrame       (AVFrame       & out     ,
                                              AVFrame       & in    ) ;
    virtual int            ConfigFrame       (const AVFrame * out     ,
                                              const AVFrame * in    ) ;

  protected:

  private:

} ;

/*!
 * libpostproc wrapper
 *
 * Steps :
 *
 * 1. getContext
 * 2. getMode
 * 3. PostProcess
 *
 */
class Q_FFMPEG_EXPORT Process
{
  public:

    enum                               {
      MMX        = PP_CPU_CAPS_MMX     ,
      MMX2       = PP_CPU_CAPS_MMX2    ,
      Now3D      = PP_CPU_CAPS_3DNOW   ,
      ALTIVEC    = PP_CPU_CAPS_ALTIVEC ,
      AUTO       = PP_CPU_CAPS_AUTO    ,

      /*! YUV Format enumerations */
      YUV420     = PP_FORMAT_420       ,
      YUV422     = PP_FORMAT_422       ,
      YUV411     = PP_FORMAT_411       ,
      YUV444     = PP_FORMAT_444       ,
      YUV440     = PP_FORMAT_440       ,

      QP2        = PP_PICT_TYPE_QP2    ,

      /*! quality is a number from 0 to MaxQuality */
      MaxQuality = PP_QUALITY_MAX
    }                                  ;

    pp_context * context ; /*! postproc context */
    QSize        size    ; /*! pp_get_context dimension */
    int          flags   ; /*! flags for pp_get_context */

    pp_mode    * mode    ; /*! postproc mode */
    int          quality ; /*! mode quality, default MaxQuality */
    QString      name    ; /*! mode name, default name as "default" */

    explicit        Process     (void) ;
    virtual        ~Process     (void) ;

    static  QString Version     (void) ;

    virtual void    Clear       (void) ;

    virtual QSize & setSize     (QSize size) ;

    virtual bool    getContext  (void) ;
    virtual bool    getContext  (int w,int h) ;
    virtual bool    getContext  (QSize size) ;
    virtual bool    getContext  (int w,int h,int flags) ;
    virtual bool    getContext  (QSize size,int flags) ;

    virtual bool    getMode     (void) ;
    virtual bool    getMode     (QString name) ;
    virtual bool    getMode     (QString name,int quality) ;

    virtual bool    PostProcess (AVFrame       & frame             ,
                                 AVFrame       & dst             ) ;
    virtual bool    PostProcess (AVFrame       * frame             ,
                                 AVFrame       * dst             ) ;
    virtual bool    PostProcess (AVFrame       * frame             ,
                                       uint8_t * dst       [ 3 ]   ,
                                 const int       dstStride [ 3 ] ) ;
    virtual bool    PostProcess (const uint8_t * src       [ 3 ]   ,
                                 const int       srcStride [ 3 ]   ,
                                       uint8_t * dst       [ 3 ]   ,
                                 const int       dstStride [ 3 ]   ,
                                 const int8_t  * QP_store          ,
                                       int       QP_stride         ,
                                       int       pict_type       ) ;
    virtual bool    PostProcess (const uint8_t * src       [ 3 ]   ,
                                 const int       srcStride [ 3 ]   ,
                                       uint8_t * dst       [ 3 ]   ,
                                 const int       dstStride [ 3 ]   ,
                                       QSize     size              ,
                                 const int8_t  * QP_store          ,
                                       int       QP_stride         ,
                                       int       pict_type       ) ;
    virtual bool    PostProcess (const uint8_t * src       [ 3 ]   ,
                                 const int       srcStride [ 3 ]   ,
                                       uint8_t * dst       [ 3 ]   ,
                                 const int       dstStride [ 3 ]   ,
                                       int       horizontalSize    ,
                                       int       verticalSize      ,
                                 const int8_t  * QP_store          ,
                                       int       QP_stride         ,
                                       int       pict_type       ) ;

  protected:

  private:

} ;

class Q_FFMPEG_EXPORT Codec
{
  public:

    AVCodecContext * context ;

    explicit Codec (void) ;
    explicit Codec (AVCodecContext * context) ;
             Codec (const Codec & codec) ;
    virtual ~Codec (void) ;

  protected:

  private:

} ;

class Q_FFMPEG_EXPORT Decoder
{
  public:

    QString              Filename      ;
    AVFormatContext    * FormatCtx     ;
    AVDictionary       * Dictionary    ;
    AVCodecContext     * VideoCtx      ;
    AVCodecContext     * AudioCtx      ;
    AVCodecContext     * CaptionCtx    ;
    AVCodec            * VideoCodec    ;
    AVCodec            * AudioCodec    ;
    AVCodec            * CaptionCodec  ;
    AVFrame            * Frame         ;
    AVFrame            * RGB           ;
    AVFrame            * AudioFrame    ;
    AVSubtitle         * Captions      ;
    AVStream           * VideoStream   ;
    AVStream           * AudioStream   ;
    AVStream           * CaptionStream ;
    struct SwsContext  * ConvertCtx    ;
    int                  VideoIndex    ;
    int                  AudioIndex    ;
    int                  Subtitle      ;
    int                  Error         ;
    bool                 isVideo       ;
    bool                 isAudio       ;
    QList<int>           Extras        ;
    SwrContext         * Resample      ;
    unsigned char      * audioConvert  ;
    QTextCodec         * TextCodec     ;

    explicit           Decoder           (void) ;
    virtual           ~Decoder           (void) ;

    virtual bool       StartAudio        (QString Filename) ;
    virtual bool       StartVideo        (QString Filename) ;
    bool               Open              (QString filename) ;
    bool               Close             (void) ;
    void               Initialize        (AVPacket * packet) ;
    void               Release           (AVPacket * packet) ;
    bool               FindStream        (void) ;
    bool               FindVideo         (void) ;
    bool               FindAudio         (void) ;
    bool               FindCaption       (void) ;
    virtual bool       OpenVideo         (void) ;
    virtual bool       OpenAudio         (void) ;
    virtual bool       OpenCaption       (void) ;
    bool               AvConvertCtx      (QSize size,int format,int method) ;
    int                Frames            (void) ;
    long long          Duration          (void) ;
    double             VideoRate         (void) ;
    double             AudioRate         (void) ;
    long long          Timestamp         (AVPacket & Packet) ;
    int                ReadPacket        (AVPacket & Packet) ;
    bool               isVideoChannel    (AVPacket & Packet) ;
    bool               isAudioChannel    (AVPacket & Packet) ;
    bool               isSubtitle        (AVPacket & Packet) ;
    long long          PTS               (AVPacket & Packet) ;
    long long          DTS               (AVPacket & Packet) ;
    int                AudioPacketSize   (int bufferSize) ;
    int                AvSampleFormat    (void) ;
    int                AvSampleRate      (void) ;
    int                AvBits            (void) ;
    bool               AvFloat           (void) ;
    int                Channels          (void) ;
    int                BitRate           (void) ;
    int                Width             (void) ;
    int                Height            (void) ;
    QString            VideoCodecName    (void) ;
    QString            AudioCodecName    (void) ;
    int                BytesPerFrame     (void) ;
    long long          AudioBufferSize   (int milliseconds) ;
    AVFrame          * AllocateFrame     (void) ;
    bool               NoPTS             (long long pts) ;
    bool               HasPTS            (long long pts) ;

    virtual void       DataChannel       (int index) ;
    virtual void       AttachmentChannel (int index) ;
    virtual void       NbChannel         (int index) ;
    virtual void       UnknownChannel    (int index) ;

    virtual int        DecodeAudio       (AVPacket      & Packet     ,
                                          unsigned char * data     ) ;
    virtual bool       DecodeImage       (AVPacket      & Packet     ,
                                          int           & gotFrame ) ;
    virtual bool       CopyImage         (int format) ;
    virtual bool       ScaleImage        (QSize size) ;
    virtual bool       DecodeCaption     (AVPacket      & Packet) ;
    virtual bool       RawSeek           (long long msecs) ;

    virtual QString    ErrorString       (int errnum) ;

  protected:

    virtual QByteArray toNative          (QString filename) ;

  private:

} ;

class Q_FFMPEG_EXPORT Encoder
{
  public:

    QString           Filename       ;
    AVCodec         * encoder        ;
    AVCodecContext  * context        ;
    ReSampleContext * resample       ;
    unsigned char   * buffer         ;
    unsigned char   * sample         ;
    int               codec          ;
    int               BytesPerFrame  ;
    int               TargetPerFrame ;
    int               SourceRate     ;
    int               SourceChannels ;
    int               SourceFormat   ;
    int               TargetRate     ;
    int               TargetChannels ;
    int               TargetFormat   ;

    explicit     Encoder       (void) ;
    virtual     ~Encoder       (void) ;

    // DeviceType : 0 - Audio , 1 - Video, 2 - Subtitle
    static bool  exists            (int codecId,int DeviceType) ;

    virtual bool OpenAudio     (int codec,int rate,int channels,int format) ; // source format
    virtual bool Compatible    (void) ;
    virtual void Resampling    (int frames) ;
    virtual bool setOutput     (int rate,int channels,int format) ;
    virtual int  FrameSize     (void) ;
    virtual int  Collect       (unsigned char * data,int length,int compressed) ;
    virtual int  Encode        (QIODevice & IO,int length,unsigned char * data,bool flush = false) ;
    virtual bool Close         (void) ;

  protected:

    virtual void addLength     (int length) ;
    virtual void addCompressed (int length) ;

  private:

} ;

Q_FFMPEG_EXPORT void RegisterFFmpeg (void) ;

}

Q_DECLARE_METATYPE(FFmpeg::CPU)
Q_DECLARE_METATYPE(FFmpeg::Rational)
Q_DECLARE_METATYPE(FFmpeg::ScaleVector)
Q_DECLARE_METATYPE(FFmpeg::ScaleFilter)
Q_DECLARE_METATYPE(FFmpeg::Scaler)
Q_DECLARE_METATYPE(FFmpeg::Resampler)
Q_DECLARE_METATYPE(FFmpeg::Process)

QT_END_NAMESPACE

#endif
