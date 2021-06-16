#include "qtffmpeg.h"

FFmpeg::Scaler:: Scaler ( void )
               : scaler ( NULL )
{
}

FFmpeg::Scaler:: Scaler ( SwsContext * s )
               : scaler (              s )
{
}

FFmpeg::Scaler:: Scaler ( ScaleFilter & src , ScaleFilter & dest )
{
  scaler = ::sws_alloc_context ( )                             ;
  ::sws_init_context ( scaler , src . filter , dest . filter ) ;
}

FFmpeg::Scaler::~Scaler(void)
{
  Clear ( ) ;
}

QString FFmpeg::Scaler::Version(void)
{
  return QString ( AV_STRINGIFY(LIBSWSCALE_VERSION) ) ;
}

const AVClass * FFmpeg::Scaler::getClass(void)
{
  return ::sws_get_class ( ) ;
}

bool FFmpeg::Scaler::isInput(enum AVPixelFormat pixfmt)
{
  return ( 0 != ::sws_isSupportedInput ( pixfmt ) ) ;
}

bool FFmpeg::Scaler::isOutput(enum AVPixelFormat pixfmt)
{
  return ( 0 != ::sws_isSupportedOutput (pixfmt) ) ;
}

bool FFmpeg::Scaler::isEndianness(enum AVPixelFormat pixfmt)
{
  return ( 0 != ::sws_isSupportedEndiannessConversion ( pixfmt ) ) ;
}

void FFmpeg::Scaler::PaletteToPacked24 (
       const uint8_t * src             ,
             uint8_t * dst             ,
       int             num_pixels      ,
       const uint8_t * palette         )
{
  ::sws_convertPalette8ToPacked24 (
    src                           ,
    dst                           ,
    num_pixels                    ,
    palette                     ) ;
}

void FFmpeg::Scaler::PaletteToPacked32 (
       const uint8_t * src             ,
             uint8_t * dst             ,
       int             num_pixels      ,
       const uint8_t * palette         )
{
  ::sws_convertPalette8ToPacked32 (
    src                           ,
    dst                           ,
    num_pixels                    ,
    palette                     ) ;
}

void FFmpeg::Scaler::Clear(void)
{
  if ( NULL == scaler ) return ;
  ::sws_freeContext ( scaler ) ;
  scaler = NULL                ;
}

bool FFmpeg::Scaler::isNull(void)
{
  return ( NULL == scaler ) ;
}

FFmpeg::Scaler & FFmpeg::Scaler::Allocate(void)
{
  Clear ( )                        ;
  scaler = ::sws_alloc_context ( ) ;
  return ( *this )                 ;
}

FFmpeg::Scaler & FFmpeg::Scaler::Initialize(void)
{
  if ( NULL == scaler ) return ( *this )      ;
  ::sws_init_context ( scaler , NULL , NULL ) ;
  return ( *this )                            ;
}

FFmpeg::Scaler & FFmpeg::Scaler::Initialize(ScaleFilter & src,ScaleFilter & dest)
{
  if ( NULL == scaler ) return ( *this )                       ;
  ::sws_init_context ( scaler , src . filter , dest . filter ) ;
  return ( *this )                                             ;
}

FFmpeg::Scaler & FFmpeg::Scaler::Get            (
                   int                srcW      ,
                   int                srcH      ,
                   enum AVPixelFormat srcFormat ,
                   int                dstW      ,
                   int                dstH      ,
                   enum AVPixelFormat dstFormat ,
                   int                flags     )
{
  Clear ( )                 ;
  scaler = ::sws_getContext (
             srcW           ,
             srcH           ,
             srcFormat      ,
             dstW           ,
             dstH           ,
             dstFormat      ,
             flags          ,
             NULL           ,
             NULL           ,
             NULL         ) ;
  return ( *this )          ;
}

FFmpeg::Scaler & FFmpeg::Scaler::Get            (
                   int                srcW      ,
                   int                srcH      ,
                   enum AVPixelFormat srcFormat ,
                   int                dstW      ,
                   int                dstH      ,
                   enum AVPixelFormat dstFormat ,
                   int                flags     ,
                   ScaleFilter      & src       ,
                   ScaleFilter      & dst       ,
                   const double     * param     )
{
  Clear ( )                 ;
  scaler = ::sws_getContext (
             srcW           ,
             srcH           ,
             srcFormat      ,
             dstW           ,
             dstH           ,
             dstFormat      ,
             flags          ,
             src . filter   ,
             dst . filter   ,
             param        ) ;
  return ( *this )          ;
}

FFmpeg::Scaler & FFmpeg::Scaler::GetCached      (
                   int                srcW      ,
                   int                srcH      ,
                   enum AVPixelFormat srcFormat ,
                   int                dstW      ,
                   int                dstH      ,
                   enum AVPixelFormat dstFormat ,
                   int                flags     )
{
  scaler = ::sws_getCachedContext (
              scaler              ,
              srcW                ,
              srcH                ,
              srcFormat           ,
              dstW                ,
              dstH                ,
              dstFormat           ,
              flags               ,
              NULL                ,
              NULL                ,
              NULL              ) ;
  return ( *this )                ;
}

FFmpeg::Scaler & FFmpeg::Scaler::GetCached      (
                   int                srcW      ,
                   int                srcH      ,
                   enum AVPixelFormat srcFormat ,
                   int                dstW      ,
                   int                dstH      ,
                   enum AVPixelFormat dstFormat ,
                   int                flags     ,
                   ScaleFilter      & src       ,
                   ScaleFilter      & dst       ,
                   const double     * param     )
{
  scaler = ::sws_getCachedContext (
             scaler               ,
             srcW                 ,
             srcH                 ,
             srcFormat            ,
             dstW                 ,
             dstH                 ,
             dstFormat            ,
             flags                ,
             src . filter         ,
             dst . filter         ,
             param              ) ;
  return ( *this )                ;
}

int FFmpeg::Scaler::Scale                 (
      const uint8_t * const srcSlice  [ ] ,
      const int             srcStride [ ] ,
      int                   srcSliceY     ,
      int                   srcSliceH     ,
      uint8_t       * const dst       [ ] ,
      const int             dstStride [ ] )
{
  if ( NULL == scaler ) return -1  ;
  return ::sws_scale ( scaler      ,
                       srcSlice    ,
                       srcStride   ,
                       srcSliceY   ,
                       srcSliceH   ,
                       dst         ,
                       dstStride ) ;
}

int FFmpeg::Scaler::setColorspace (
      const int inv_table[4]      ,
      int       srcRange          ,
      const int table    [4]      ,
      int       dstRange          ,
      int       brightness        ,
      int       contrast          ,
      int       saturation        )
{
  if ( NULL == scaler ) return -1   ;
  return ::sws_setColorspaceDetails (
           scaler                   ,
           inv_table                ,
           srcRange                 ,
           table                    ,
           dstRange                 ,
           brightness               ,
           contrast                 ,
           saturation             ) ;
}

int FFmpeg::Scaler::getColorspace (
      int ** inv_table            ,
      int *  srcRange             ,
      int ** table                ,
      int *  dstRange             ,
      int *  brightness           ,
      int *  contrast             ,
      int *  saturation           )
{
  if ( NULL == scaler ) return -1   ;
  return ::sws_getColorspaceDetails (
           scaler                   ,
           inv_table                ,
           srcRange                 ,
           table                    ,
           dstRange                 ,
           brightness               ,
           contrast                 ,
           saturation             ) ;
}
