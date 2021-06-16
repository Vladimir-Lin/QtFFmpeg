#include "qtffmpeg.h"

FFmpeg::Codec:: Codec   ( void )
              : context ( NULL )
{
}

FFmpeg::Codec:: Codec   ( AVCodecContext * c )
              : context (                  c )
{
}

FFmpeg::Codec:: Codec   ( const Codec & c )
              : context ( c . context     )
{
}

FFmpeg::Codec::~Codec (void)
{
}
