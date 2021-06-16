#include "qtffmpeg.h"

FFmpeg::ScaleFilter:: ScaleFilter (void)
                    : filter      (NULL)
{
}

FFmpeg::ScaleFilter:: ScaleFilter ( SwsFilter * f )
                    : filter      (             f )
{
}

FFmpeg::ScaleFilter:: ScaleFilter ( float lumaGBlur     ,
                                    float chromaGBlur   ,
                                    float lumaSharpen   ,
                                    float chromaSharpen ,
                                    float chromaHShift  ,
                                    float chromaVShift  ,
                                    int   verbose       )
{
  filter = ::sws_getDefaultFilter (
             lumaGBlur            ,
             chromaGBlur          ,
             lumaSharpen          ,
             chromaSharpen        ,
             chromaHShift         ,
             chromaVShift         ,
             verbose            ) ;
}

FFmpeg::ScaleFilter::~ScaleFilter(void)
{
  Clear ( ) ;
}

void FFmpeg::ScaleFilter::Clear(void)
{
  if ( NULL == filter ) return ;
  ::sws_freeFilter ( filter )  ;
  filter = NULL                ;
}

bool FFmpeg::ScaleFilter::isNull(void)
{
  return ( NULL == filter ) ;
}

FFmpeg::ScaleFilter & FFmpeg::ScaleFilter::Allocate (
                        float lumaGBlur             ,
                        float chromaGBlur           ,
                        float lumaSharpen           ,
                        float chromaSharpen         ,
                        float chromaHShift          ,
                        float chromaVShift          ,
                        int   verbose               )
{
  Clear ( )                       ;
  filter = ::sws_getDefaultFilter (
             lumaGBlur            ,
             chromaGBlur          ,
             lumaSharpen          ,
             chromaSharpen        ,
             chromaHShift         ,
             chromaVShift         ,
             verbose            ) ;
  return ( *this )                ;
}
