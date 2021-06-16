#include "qtffmpeg.h"

#pragma message("Rational requires to be completed")

FFmpeg::Rational:: Rational    ( void )
                 : numerator   ( 0    )
                 , denominator ( 0    )
{
}

FFmpeg::Rational:: Rational    ( int num , int den )
                 : numerator   (     num           )
                 , denominator (               den )
{
}

FFmpeg::Rational:: Rational    ( const Rational & r )
                 : numerator   ( r . numerator      )
                 , denominator ( r . denominator    )
{
}

FFmpeg::Rational:: Rational    ( const AVRational & r )
                 : numerator   ( r . num              )
                 , denominator ( r . den              )
{
}

FFmpeg::Rational:: Rational    ( AVRational * r )
                 : numerator   ( 0              )
                 , denominator ( 0              )
{
  if ( NULL != r )         {
    numerator   = r -> num ;
    denominator = r -> den ;
  }                        ;
}

FFmpeg::Rational::~Rational(void)
{
}

AVRational FFmpeg::Rational::To(void)
{
  AVRational V          ;
  V . num = numerator   ;
  V . den = denominator ;
  return V              ;
}

void FFmpeg::Rational::To(AVRational & V)
{
  V . num = numerator   ;
  V . den = denominator ;
}

int FFmpeg::Rational::compare(Rational & A)
{
  AVRational V         ;
  A . To ( V )         ;
  return compare ( V ) ;
}

int FFmpeg::Rational::compare(AVRational & V)
{
  AVRational A              ;
  To ( A )                  ;
  return av_cmp_q ( A , V ) ;
}

bool FFmpeg::Rational::reduce(int64_t maxv)
{
  int num                                                          ;
  int den                                                          ;
  int r                                                            ;
  r = ::av_reduce ( &num , &den , numerator , denominator , maxv ) ;
  if ( 1 != r ) return false                                       ;
  numerator   = num                                                ;
  denominator = den                                                ;
  return true                                                      ;
}

FFmpeg::Rational & FFmpeg::Rational::operator *= (Rational & av)
{
  AVRational A              ;
  AVRational B              ;
  AVRational C              ;
  av . To         ( B     ) ;
  To              (     C ) ;
  A  = ::av_mul_q ( B , C ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

FFmpeg::Rational & FFmpeg::Rational::operator *= (AVRational & B)
{
  AVRational A              ;
  AVRational C              ;
  To              (     C ) ;
  A  = ::av_mul_q ( B , C ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

FFmpeg::Rational & FFmpeg::Rational::operator /= (Rational & av)
{
  AVRational A              ;
  AVRational B              ;
  AVRational C              ;
  av . To         ( B     ) ;
  To              (     C ) ;
  A  = ::av_div_q ( B , C ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

FFmpeg::Rational & FFmpeg::Rational::operator /= (AVRational & B)
{
  AVRational A              ;
  AVRational C              ;
  To              (     C ) ;
  A  = ::av_div_q ( B , C ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

FFmpeg::Rational & FFmpeg::Rational::operator += (Rational & av)
{
  AVRational A              ;
  AVRational B              ;
  AVRational C              ;
  av . To         ( B     ) ;
  To              (     C ) ;
  A  = ::av_add_q ( B , C ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

FFmpeg::Rational & FFmpeg::Rational::operator += (AVRational & B)
{
  AVRational A              ;
  AVRational C              ;
  To              (     C ) ;
  A  = ::av_add_q ( B , C ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

FFmpeg::Rational & FFmpeg::Rational::operator -= (Rational & av)
{
  AVRational A              ;
  AVRational B              ;
  AVRational C              ;
  av . To         ( B     ) ;
  To              (     C ) ;
  A  = ::av_sub_q ( B , C ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

FFmpeg::Rational & FFmpeg::Rational::operator -= (AVRational & B)
{
  AVRational A              ;
  AVRational C              ;
  To              (     C ) ;
  A  = ::av_sub_q ( B , C ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

void FFmpeg::Rational::Invert(void)
{
  int t                     ;
  t           = denominator ;
  denominator = numerator   ;
  numerator   = t           ;
}

FFmpeg::Rational FFmpeg::Rational::Inversion(void)
{
  return Rational ( denominator , numerator ) ;
}

FFmpeg::Rational & FFmpeg::Rational::FromDouble(double d,int maxv)
{
  AVRational A              ;
  A = ::av_d2q ( d , maxv ) ;
  numerator   = A . num     ;
  denominator = A . den     ;
  return (*this)            ;
}

FFmpeg::Rational & FFmpeg::Rational::operator = (double d)
{
  return FromDouble ( d ) ;
}

int FFmpeg::Rational::Nearer(Rational & q1,Rational & q2)
{
  AVRational A                       ;
  AVRational B                       ;
  AVRational C                       ;
  To      ( A )                      ;
  q1 . To ( B )                      ;
  q2 . To ( C )                      ;
  return ::av_nearer_q ( A , B , C ) ;
}

int FFmpeg::Rational::Nearer(AVRational & B,AVRational & C)
{
  AVRational A                       ;
  To ( A )                           ;
  return ::av_nearer_q ( A , B , C ) ;
}

int FFmpeg::Rational::Nearest(const AVRational * Q)
{
  if ( NULL == Q ) return -1               ;
  AVRational A                             ;
  To ( A )                                 ;
  return ::av_find_nearest_q_idx ( A , Q ) ;
}

quint32 FFmpeg::Rational::ieeeFloat(void)
{
  AVRational A                         ;
  To ( A )                             ;
  return (quint32) av_q2intfloat ( A ) ;
}
