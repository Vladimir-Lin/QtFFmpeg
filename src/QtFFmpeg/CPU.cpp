#include "qtffmpeg.h"

void FFmpeg::RegisterFFmpeg(void)
{
  qRegisterMetaType < FFmpeg::CPU         > ( "FFmpeg::CPU"         ) ;
  qRegisterMetaType < FFmpeg::Rational    > ( "FFmpeg::Rational"    ) ;
  qRegisterMetaType < FFmpeg::ScaleVector > ( "FFmpeg::ScaleVector" ) ;
  qRegisterMetaType < FFmpeg::ScaleFilter > ( "FFmpeg::ScaleFilter" ) ;
  qRegisterMetaType < FFmpeg::Scaler      > ( "FFmpeg::Scaler"      ) ;
  qRegisterMetaType < FFmpeg::Resampler   > ( "FFmpeg::Resampler"   ) ;
  qRegisterMetaType < FFmpeg::Process     > ( "FFmpeg::Process"     ) ;
  qRegisterMetaType < FFmpeg::Codec       > ( "FFmpeg::Codec"       ) ;
}

FFmpeg::CPU:: CPU(void)
{
}

FFmpeg::CPU:: CPU(const CPU &)
{
}

FFmpeg::CPU::~CPU(void)
{
}

int FFmpeg::CPU::Processors(void)
{
  return ::av_cpu_count ( ) ;
}

int FFmpeg::CPU::Flags(void)
{
  return ::av_get_cpu_flags ( ) ;
}

void FFmpeg::CPU::setFlags(int flags)
{
  ::av_force_cpu_flags ( flags ) ;
}

int FFmpeg::CPU::Parse(unsigned int & flags,const char * string)
{
  return ::av_parse_cpu_caps ( &flags , string ) ;
}

int FFmpeg::CPU::Parse(unsigned int & flags,QString string)
{
  return ::av_parse_cpu_caps ( &flags , string . toUtf8 ( ) . constData ( ) ) ;
}
