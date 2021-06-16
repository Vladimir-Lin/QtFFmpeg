#include "qtffmpeg.h"

FFmpeg::ScaleVector:: ScaleVector (void)
                    : vector      (NULL)
{
}

FFmpeg::ScaleVector:: ScaleVector (int length)
{
  vector = ::sws_allocVec ( length ) ;
}

FFmpeg::ScaleVector:: ScaleVector ( const ScaleVector & v )
{
  if ( NULL == v . vector )                {
    vector = NULL                          ;
  } else                                   {
    vector = ::sws_cloneVec ( v . vector ) ;
  }                                        ;
}

FFmpeg::ScaleVector:: ScaleVector ( SwsVector * v )
                    : vector      (             v )
{
}

FFmpeg::ScaleVector::~ScaleVector(void)
{
  Clear ( ) ;
}

void FFmpeg::ScaleVector::Clear(void)
{
  if ( NULL == vector ) return ;
  ::sws_freeVec ( vector )     ;
}

bool FFmpeg::ScaleVector::isNull(void)
{
  return ( NULL == vector ) ;
}

FFmpeg::ScaleVector &  FFmpeg::ScaleVector::Allocate(int length)
{
  Clear ( )                          ;
  vector = ::sws_allocVec ( length ) ;
  return ( *this )                   ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::Constant(double c,int length)
{
  Clear ( )                                 ;
  vector = ::sws_getConstVec ( c , length ) ;
  return ( *this )                          ;
}

FFmpeg::ScaleVector &  FFmpeg::ScaleVector::Gaussian(double variance,double quality)
{
  Clear ( )                                            ;
  vector = ::sws_getGaussianVec ( variance , quality ) ;
  return ( *this )                                     ;
}

FFmpeg::ScaleVector &  FFmpeg::ScaleVector::Identity(void)
{
  Clear ( )                         ;
  vector = ::sws_getIdentityVec ( ) ;
  return ( *this )                  ;
}

FFmpeg::ScaleVector &  FFmpeg::ScaleVector::Scale(double scalar)
{
  if ( NULL == vector ) return ( *this ) ;
  ::sws_scaleVec ( vector , scalar )     ;
  return ( *this )                       ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::Normalize(double height)
{
  if ( NULL == vector ) return ( *this ) ;
  ::sws_normalizeVec ( vector , height ) ;
  return ( *this )                       ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::Shift(int shift)
{
  if ( NULL == vector ) return ( *this ) ;
  ::sws_shiftVec ( vector , shift )      ;
  return ( *this )                       ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::Conv(ScaleVector & v)
{
  if ( NULL ==     vector ) return ( *this ) ;
  if ( NULL == v . vector ) return ( *this ) ;
  ::sws_convVec ( vector , v . vector )      ;
  return ( *this )                           ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::Add(ScaleVector & v)
{
  if ( NULL ==     vector ) return ( *this ) ;
  if ( NULL == v . vector ) return ( *this ) ;
  ::sws_addVec ( vector , v . vector )       ;
  return ( *this )                           ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::Subtract(ScaleVector & v)
{
  if ( NULL ==     vector ) return ( *this ) ;
  if ( NULL == v . vector ) return ( *this ) ;
  ::sws_subVec ( vector , v . vector )       ;
  return ( *this )                           ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::operator += (ScaleVector & v)
{
  if ( NULL ==     vector ) return ( *this ) ;
  if ( NULL == v . vector ) return ( *this ) ;
  ::sws_addVec ( vector , v . vector )       ;
  return ( *this )                           ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::operator -= (ScaleVector & v)
{
  if ( NULL ==     vector ) return ( *this ) ;
  if ( NULL == v . vector ) return ( *this ) ;
  ::sws_subVec ( vector , v . vector )       ;
  return ( *this )                           ;
}

FFmpeg::ScaleVector & FFmpeg::ScaleVector::operator = (ScaleVector & v)
{
  Clear ( )                                  ;
  if ( NULL == v . vector ) return ( *this ) ;
  vector = ::sws_cloneVec ( v . vector )     ;
  return ( *this )                           ;
}
