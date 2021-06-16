#include "qtffmpeg.h"
#include "libpostproc/version.h"
#include "libpostproc/postprocess.h"

FFmpeg::Process:: Process ( void )
                : mode    ( NULL )
                , context ( NULL )
{
  flags   = MMX | MMX2 | YUV420   ;
  quality = MaxQuality            ;
  name    = QString ( "default" ) ;
}

FFmpeg::Process::~Process(void)
{
  Clear ( ) ;
}

/*! the code was within libpostproc/version.h */
QString FFmpeg::Process::Version(void)
{
  return QString ( AV_STRINGIFY ( LIBPOSTPROC_VERSION ) ) ;
}

void FFmpeg::Process::Clear(void)
{
  if ( NULL != mode    ) ::pp_free_mode    ( mode    ) ;
  if ( NULL != context ) ::pp_free_context ( context ) ;
  mode    = NULL                                       ;
  context = NULL                                       ;
}

QSize & FFmpeg::Process::setSize(QSize s)
{
  size = s    ;
  return size ;
}

bool FFmpeg::Process::getContext (void)
{
  return getContext ( size , flags ) ;
}

bool FFmpeg::Process::getContext (int w,int h)
{
  return getContext ( w , h , flags ) ;
}

bool FFmpeg::Process::getContext (QSize s)
{
  return getContext ( s . width ( ) , s . height ( ) ) ;
}

bool FFmpeg::Process::getContext (int w,int h,int f)
{
  flags = f                                            ;
  size  = QSize ( w , h )                              ;
  if ( NULL != context ) ::pp_free_context ( context ) ;
  context = ::pp_get_context ( w , h , f )             ;
  return ( NULL != context )                           ;
}

bool FFmpeg::Process::getContext (QSize s,int f)
{
  return getContext ( s . width ( ) , s . height ( ) , f ) ;
}

bool FFmpeg::Process::getMode(void)
{
  return getMode ( name ) ;
}

bool FFmpeg::Process::getMode(QString n)
{
  return getMode ( n , quality ) ;
}

bool FFmpeg::Process::getMode(QString n,int q)
{
  name    = n                                 ;
  quality = q                                 ;
  if ( NULL != mode ) ::pp_free_mode ( mode ) ;
  mode    = NULL                              ;
  if ( name . length ( ) <= 0 ) return false  ;
  mode    = ::pp_get_mode_by_name_and_quality (
              n . toUtf8 ( ) . constData ( )  ,
              quality                       ) ;
  return ( NULL != mode )                     ;
}

bool FFmpeg::Process::PostProcess(AVFrame & frame,AVFrame & dst)
{
  return PostProcess ( &frame , &dst ) ;
}

bool FFmpeg::Process::PostProcess(AVFrame * frame,AVFrame * dst)
{
  if ( NULL == dst   ) return false                            ;
  return PostProcess ( frame , dst -> data , dst -> linesize ) ;
}

bool FFmpeg::Process::PostProcess      (
       AVFrame       * frame           ,
             uint8_t * dst       [ 3 ] ,
       const int       dstStride [ 3 ] )
{
  if ( NULL == frame ) return false ;
  const uint8_t * s [ 3 ] =         {
      frame -> data [ 0 ]           ,
      frame -> data [ 1 ]           ,
      frame -> data [ 2 ]         } ;
  return PostProcess                (
           s                        ,
           frame -> linesize        ,
           dst                      ,
           dstStride                ,
           frame -> qscale_table    ,
           frame -> qstride         ,
           frame -> pict_type     ) ;
}

bool FFmpeg::Process::PostProcess      (
       const uint8_t * src       [ 3 ] ,
       const int       srcStride [ 3 ] ,
             uint8_t * dst       [ 3 ] ,
       const int       dstStride [ 3 ] ,
       const int8_t  * QP_store        ,
             int       QP_stride       ,
             int       pict_type       )
{
  return PostProcess   (
           src         ,
           srcStride   ,
           dst         ,
           dstStride   ,
           size        ,
           QP_store    ,
           QP_stride   ,
           pict_type ) ;
}

bool FFmpeg::Process::PostProcess      (
       const uint8_t * src       [ 3 ] ,
       const int       srcStride [ 3 ] ,
             uint8_t * dst       [ 3 ] ,
       const int       dstStride [ 3 ] ,
             QSize     s               ,
       const int8_t  * QP_store        ,
             int       QP_stride       ,
             int       pict_type       )
{
  return PostProcess      (
           src            ,
           srcStride      ,
           dst            ,
           dstStride      ,
           s . width  ( ) ,
           s . height ( ) ,
           QP_store       ,
           QP_stride      ,
           pict_type    ) ;
}

bool FFmpeg::Process::PostProcess      (
       const uint8_t * src       [ 3 ] ,
       const int       srcStride [ 3 ] ,
             uint8_t * dst       [ 3 ] ,
       const int       dstStride [ 3 ] ,
             int       horizontalSize  ,
             int       verticalSize    ,
       const int8_t  * QP_store        ,
             int       QP_stride       ,
             int       pict_type       )
{
  if ( NULL == mode        ) return false ;
  if ( NULL == context     ) return false ;
  if ( NULL == QP_store    ) return false ;
  if ( horizontalSize <= 0 ) return false ;
  if ( verticalSize   <= 0 ) return false ;
  ::pp_postprocess                        (
    src                                   ,
    srcStride                             ,
    dst                                   ,
    dstStride                             ,
    horizontalSize                        ,
    verticalSize                          ,
    QP_store                              ,
    QP_stride                             ,
    mode                                  ,
    context                               ,
    pict_type                           ) ;
  return true                             ;
}
