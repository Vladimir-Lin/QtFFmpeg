#include "qtffmpeg.h"
#include "libswresample/version.h"
#include "libswresample/swresample.h"

FFmpeg::Resampler:: Resampler(void)
                  : resampler(NULL)
{
}

FFmpeg::Resampler::~Resampler(void)
{
  Close ( ) ;
  Clear ( ) ;
}

QString FFmpeg::Resampler::Version(void)
{
  return QString ( AV_STRINGIFY(LIBSWRESAMPLE_VERSION) ) ;
}

const AVClass * FFmpeg::Resampler::getClass  (void)
{
  return ::swr_get_class ( ) ;
}

void FFmpeg::Resampler::Clear(void)
{
  if ( NULL == resampler ) return ;
  ::swr_free ( &resampler )       ;
  resampler = NULL                ;
}

bool FFmpeg::Resampler::isNull(void)
{
  return ( NULL == resampler ) ;
}

FFmpeg::Resampler & FFmpeg::Resampler::Allocate(void)
{
  Clear ( )                   ;
  resampler = ::swr_alloc ( ) ;
  return ( *this )            ;
}

int FFmpeg::Resampler::Initialize(void)
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA ;
  return ::swr_init ( resampler )                     ;
}

bool FFmpeg::Resampler::isInitialize (void)
{
  if ( NULL == resampler ) return false           ;
  return ( swr_is_initialized ( resampler ) > 0 ) ;
}

void FFmpeg::Resampler::Close(void)
{
  if ( NULL == resampler ) return ;
  ::swr_close ( resampler )       ;
}

bool FFmpeg::Resampler::setOpts            (
       qint64              out_ch_layout   ,
       enum AVSampleFormat out_sample_fmt  ,
       int                 out_sample_rate ,
       qint64              in_ch_layout    ,
       enum AVSampleFormat in_sample_fmt   ,
       int                 in_sample_rate  ,
       int                 log_offset      ,
       void              * log_ctx         )
{
  resampler = ::swr_alloc_set_opts        (
                          resampler       ,
                (int64_t) out_ch_layout   ,
                          out_sample_fmt  ,
                          out_sample_rate ,
                (int64_t) in_ch_layout    ,
                          in_sample_fmt   ,
                          in_sample_rate  ,
                          log_offset      ,
                          log_ctx       ) ;
  return ( NULL != resampler )            ;
}

int FFmpeg::Resampler::Convert   (
            uint8_t ** out       ,
            int        out_count ,
      const uint8_t ** in        ,
            int        in_count  )
{
  if ( NULL == resampler ) return -1 ;
  return ::swr_convert               (
           resampler                 ,
           out                       ,
           out_count                 ,
           in                        ,
           in_count                ) ;
}

qint64 FFmpeg::Resampler::NextPTS(qint64 pts)
{
  if ( NULL == resampler ) return -1                           ;
  return (qint64) ::swr_next_pts ( resampler , (int64_t) pts ) ;
}

int FFmpeg::Resampler::setCompensation (
      int sample_delta                 ,
      int compensation_distance        )
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA ;
  return ::swr_set_compensation                       (
           resampler                                  ,
           sample_delta                               ,
           compensation_distance                    ) ;
}

int FFmpeg::Resampler::setChannelMapping (const int * channel_map)
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA          ;
  return ::swr_set_channel_mapping ( resampler , channel_map ) ;
}

int FFmpeg::Resampler::setMatrix(const double * m,int stride)
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA ;
  return ::swr_set_matrix ( resampler , m , stride )  ;
}

int FFmpeg::Resampler::dropOutput(int c)
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA ;
  return ::swr_drop_output ( resampler , c )          ;
}

int FFmpeg::Resampler::InjectSilence(int c)
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA ;
  return ::swr_inject_silence ( resampler , c )       ;
}

qint64 FFmpeg::Resampler::getDelay(qint64 base)
{
  if ( NULL == resampler ) return 0                              ;
  return (qint64) ::swr_get_delay ( resampler , (int64_t) base ) ;
}

int FFmpeg::Resampler::getOutSamples(int in_samples)
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA     ;
  return ::swr_get_out_samples ( resampler , in_samples ) ;
}

int FFmpeg::Resampler::ConvertFrame(AVFrame & o,AVFrame & i)
{
  return ConvertFrame ( &o , &i ) ;
}

int FFmpeg::Resampler::ConvertFrame(AVFrame * o,const AVFrame * i)
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA ;
  return ::swr_convert_frame ( resampler , o , i )    ;
}

int FFmpeg::Resampler::ConfigFrame(AVFrame & o,AVFrame & i)
{
  return ConfigFrame ( &o , &i ) ;
}

int FFmpeg::Resampler::ConfigFrame(const AVFrame * o,const AVFrame * i)
{
  if ( NULL == resampler ) return AVERROR_INVALIDDATA ;
  return ::swr_config_frame ( resampler , o , i )     ;
}
