#include <qtffmpeg.h>

typedef struct           {
  int          codec     ;
  const char * extension ;
} VideoExt               ;

VideoExt EXTs [ ] =                          {
  { AV_CODEC_ID_MPEG1VIDEO        , ""     } ,
  { AV_CODEC_ID_MPEG2VIDEO        , ""     } ,
  { AV_CODEC_ID_MPEG2VIDEO_XVMC   , ""     } ,
  { AV_CODEC_ID_H261              , ""     } ,
  { AV_CODEC_ID_H263              , ""     } ,
  { AV_CODEC_ID_RV10              , ""     } ,
  { AV_CODEC_ID_RV20              , ""     } ,
  { AV_CODEC_ID_MJPEG             , ""     } ,
  { AV_CODEC_ID_MJPEGB            , ""     } ,
  { AV_CODEC_ID_LJPEG             , ""     } ,
  { AV_CODEC_ID_SP5X              , ""     } ,
  { AV_CODEC_ID_JPEGLS            , ""     } ,
  { AV_CODEC_ID_MPEG4             , "mp4"  } ,
  { AV_CODEC_ID_RAWVIDEO          , ""     } ,
  { AV_CODEC_ID_MSMPEG4V1         , "avi"  } ,
  { AV_CODEC_ID_MSMPEG4V2         , "avi"  } ,
  { AV_CODEC_ID_MSMPEG4V3         , "avi"  } ,
  { AV_CODEC_ID_WMV1              , "wmv"  } ,
  { AV_CODEC_ID_WMV2              , "wmv"  } ,
  { AV_CODEC_ID_H263P             , ""     } ,
  { AV_CODEC_ID_H263I             , ""     } ,
  { AV_CODEC_ID_FLV1              , "flv"  } ,
  { AV_CODEC_ID_SVQ1              , ""     } ,
  { AV_CODEC_ID_SVQ3              , ""     } ,
  { AV_CODEC_ID_DVVIDEO           , ""     } ,
  { AV_CODEC_ID_HUFFYUV           , ""     } ,
  { AV_CODEC_ID_CYUV              , ""     } ,
  { AV_CODEC_ID_H264              , ""     } ,
  { AV_CODEC_ID_INDEO3            , ""     } ,
  { AV_CODEC_ID_VP3               , ""     } ,
  { AV_CODEC_ID_THEORA            , ""     } ,
  { AV_CODEC_ID_ASV1              , "asv"  } ,
  { AV_CODEC_ID_ASV2              , "asf"  } ,
  { AV_CODEC_ID_FFV1              , ""     } ,
  { AV_CODEC_ID_4XM               , ""     } ,
  { AV_CODEC_ID_VCR1              , ""     } ,
  { AV_CODEC_ID_CLJR              , ""     } ,
  { AV_CODEC_ID_MDEC              , ""     } ,
  { AV_CODEC_ID_ROQ               , ""     } ,
  { AV_CODEC_ID_INTERPLAY_VIDEO   , ""     } ,
  { AV_CODEC_ID_XAN_WC3           , ""     } ,
  { AV_CODEC_ID_XAN_WC4           , ""     } ,
  { AV_CODEC_ID_RPZA              , ""     } ,
  { AV_CODEC_ID_CINEPAK           , ""     } ,
  { AV_CODEC_ID_WS_VQA            , ""     } ,
  { AV_CODEC_ID_MSRLE             , ""     } ,
  { AV_CODEC_ID_MSVIDEO1          , ""     } ,
  { AV_CODEC_ID_IDCIN             , ""     } ,
  { AV_CODEC_ID_8BPS              , ""     } ,
  { AV_CODEC_ID_SMC               , ""     } ,
  { AV_CODEC_ID_FLIC              , ""     } ,
  { AV_CODEC_ID_TRUEMOTION1       , ""     } ,
  { AV_CODEC_ID_VMDVIDEO          , ""     } ,
  { AV_CODEC_ID_MSZH              , ""     } ,
  { AV_CODEC_ID_ZLIB              , ""     } ,
  { AV_CODEC_ID_QTRLE             , ""     } ,
  { AV_CODEC_ID_TSCC              , ""     } ,
  { AV_CODEC_ID_ULTI              , ""     } ,
  { AV_CODEC_ID_QDRAW             , ""     } ,
  { AV_CODEC_ID_VIXL              , ""     } ,
  { AV_CODEC_ID_QPEG              , ""     } ,
  { AV_CODEC_ID_PGMYUV            , ""     } ,
  { AV_CODEC_ID_PAM               , ""     } ,
  { AV_CODEC_ID_FFVHUFF           , ""     } ,
  { AV_CODEC_ID_RV30              , ""     } ,
  { AV_CODEC_ID_RV40              , ""     } ,
  { AV_CODEC_ID_VC1               , ""     } ,
  { AV_CODEC_ID_WMV3              , "wmv"  } ,
  { AV_CODEC_ID_LOCO              , ""     } ,
  { AV_CODEC_ID_WNV1              , ""     } ,
  { AV_CODEC_ID_AASC              , ""     } ,
  { AV_CODEC_ID_INDEO2            , ""     } ,
  { AV_CODEC_ID_FRAPS             , ""     } ,
  { AV_CODEC_ID_TRUEMOTION2       , ""     } ,
  { AV_CODEC_ID_CSCD              , ""     } ,
  { AV_CODEC_ID_MMVIDEO           , ""     } ,
  { AV_CODEC_ID_ZMBV              , ""     } ,
  { AV_CODEC_ID_AVS               , ""     } ,
  { AV_CODEC_ID_SMACKVIDEO        , ""     } ,
  { AV_CODEC_ID_NUV               , ""     } ,
  { AV_CODEC_ID_KMVC              , ""     } ,
  { AV_CODEC_ID_FLASHSV           , ""     } ,
  { AV_CODEC_ID_CAVS              , ""     } ,
  { AV_CODEC_ID_VMNC              , ""     } ,
  { AV_CODEC_ID_VP5               , ""     } ,
  { AV_CODEC_ID_VP6               , ""     } ,
  { AV_CODEC_ID_VP6F              , ""     } ,
  { AV_CODEC_ID_DSICINVIDEO       , ""     } ,
  { AV_CODEC_ID_TIERTEXSEQVIDEO   , ""     } ,
  { AV_CODEC_ID_DXA               , ""     } ,
  { AV_CODEC_ID_DNXHD             , ""     } ,
  { AV_CODEC_ID_THP               , ""     } ,
  { AV_CODEC_ID_SGI               , "sgi"  } ,
  { AV_CODEC_ID_C93               , ""     } ,
  { AV_CODEC_ID_BETHSOFTVID       , ""     } ,
  { AV_CODEC_ID_PTX               , ""     } ,
  { AV_CODEC_ID_TXD               , ""     } ,
  { AV_CODEC_ID_VP6A              , ""     } ,
  { AV_CODEC_ID_AMV               , ""     } ,
  { AV_CODEC_ID_VB                , ""     } ,
  { AV_CODEC_ID_PCX               , ""     } ,
  { AV_CODEC_ID_SUNRAST           , ""     } ,
  { AV_CODEC_ID_INDEO4            , ""     } ,
  { AV_CODEC_ID_INDEO5            , ""     } ,
  { AV_CODEC_ID_MIMIC             , ""     } ,
  { AV_CODEC_ID_RL2               , ""     } ,
  { AV_CODEC_ID_ESCAPE124         , ""     } ,
  { AV_CODEC_ID_DIRAC             , ""     } ,
  { AV_CODEC_ID_BFI               , ""     } ,
  { AV_CODEC_ID_CMV               , ""     } ,
  { AV_CODEC_ID_MOTIONPIXELS      , ""     } ,
  { AV_CODEC_ID_TGV               , ""     } ,
  { AV_CODEC_ID_TGQ               , ""     } ,
  { AV_CODEC_ID_TQI               , ""     } ,
  { AV_CODEC_ID_AURA              , ""     } ,
  { AV_CODEC_ID_AURA2             , ""     } ,
  { AV_CODEC_ID_V210X             , ""     } ,
  { AV_CODEC_ID_TMV               , ""     } ,
  { AV_CODEC_ID_V210              , ""     } ,
  { AV_CODEC_ID_DPX               , ""     } ,
  { AV_CODEC_ID_MAD               , ""     } ,
  { AV_CODEC_ID_FRWU              , ""     } ,
  { AV_CODEC_ID_FLASHSV2          , ""     } ,
  { AV_CODEC_ID_CDGRAPHICS        , ""     } ,
  { AV_CODEC_ID_R210              , ""     } ,
  { AV_CODEC_ID_ANM               , ""     } ,
  { AV_CODEC_ID_BINKVIDEO         , ""     } ,
  { AV_CODEC_ID_IFF_ILBM          , ""     } ,
  { AV_CODEC_ID_KGV1              , ""     } ,
  { AV_CODEC_ID_YOP               , ""     } ,
  { AV_CODEC_ID_VP8               , ""     } ,
  { AV_CODEC_ID_PICTOR            , ""     } ,
  { AV_CODEC_ID_ANSI              , ""     } ,
  { AV_CODEC_ID_A64_MULTI         , ""     } ,
  { AV_CODEC_ID_A64_MULTI5        , ""     } ,
  { AV_CODEC_ID_R10K              , ""     } ,
  { AV_CODEC_ID_MXPEG             , ""     } ,
  { AV_CODEC_ID_LAGARITH          , ""     } ,
  { AV_CODEC_ID_PRORES            , ""     } ,
  { AV_CODEC_ID_JV                , ""     } ,
  { AV_CODEC_ID_DFA               , ""     } ,
  { AV_CODEC_ID_WMV3IMAGE         , ""     } ,
  { AV_CODEC_ID_VC1IMAGE          , ""     } ,
  { AV_CODEC_ID_UTVIDEO           , ""     } ,
  { AV_CODEC_ID_BMV_VIDEO         , ""     } ,
  { AV_CODEC_ID_VBLE              , ""     } ,
  { AV_CODEC_ID_DXTORY            , ""     } ,
  { AV_CODEC_ID_V410              , ""     } ,
  { AV_CODEC_ID_XWD               , ""     } ,
  { AV_CODEC_ID_CDXL              , ""     } ,
  { AV_CODEC_ID_XBM               , ""     } ,
  { AV_CODEC_ID_ZEROCODEC         , ""     } ,
  { AV_CODEC_ID_MSS1              , ""     } ,
  { AV_CODEC_ID_MSA1              , ""     } ,
  { AV_CODEC_ID_TSCC2             , ""     } ,
  { AV_CODEC_ID_MTS2              , ""     } ,
  { AV_CODEC_ID_CLLC              , ""     } ,
  { AV_CODEC_ID_MSS2              , ""     } ,
  { AV_CODEC_ID_VP9               , ""     } ,
  { AV_CODEC_ID_AIC               , ""     } ,
  { AV_CODEC_ID_HNM4_VIDEO        , ""     } ,
  { AV_CODEC_ID_BRENDER_PIX       , ""     } ,
  { AV_CODEC_ID_Y41P              , ""     } ,
  { AV_CODEC_ID_ESCAPE130         , ""     } ,
  { AV_CODEC_ID_EXR               , ""     } ,
  { AV_CODEC_ID_AVRP              , ""     } ,
  { AV_CODEC_ID_012V              , ""     } ,
  { AV_CODEC_ID_G2M               , ""     } ,
  { AV_CODEC_ID_AVUI              , ""     } ,
  { AV_CODEC_ID_AYUV              , ""     } ,
  { AV_CODEC_ID_TARGA_Y216        , ""     } ,
  { AV_CODEC_ID_V308              , ""     } ,
  { AV_CODEC_ID_V408              , ""     } ,
  { AV_CODEC_ID_YUV4              , ""     } ,
  { AV_CODEC_ID_SANM              , ""     } ,
  { AV_CODEC_ID_PAF_VIDEO         , ""     } ,
  { AV_CODEC_ID_AVRN              , ""     } ,
  { AV_CODEC_ID_CPIA              , ""     } ,
  { AV_CODEC_ID_XFACE             , ""     } ,
  { AV_CODEC_ID_SGIRLE            , ""     } ,
  { AV_CODEC_ID_MVC1              , ""     } ,
  { AV_CODEC_ID_MVC2              , ""     } ,
  { AV_CODEC_ID_ALIAS_PIX         , ""     } ,
  { AV_CODEC_ID_FIC               , ""     } ,
  { AV_CODEC_ID_VP7               , ""     } ,
  { AV_CODEC_ID_SNOW              , ""     } ,
  { AV_CODEC_ID_WEBP              , ""     } ,
  { AV_CODEC_ID_SMVJPEG           , ""     } ,
  { AV_CODEC_ID_APNG              , ""     } ,
  { AV_CODEC_ID_DAALA             , ""     } ,
  { AV_CODEC_ID_CFHD              , ""     } ,
  { AV_CODEC_ID_HEVC              , ""     } ,
  { AV_CODEC_ID_HQX               , ""     } ,
  { AV_CODEC_ID_TDSC              , ""     } ,
  { AV_CODEC_ID_HQ_HQA            , ""     } ,
  { AV_CODEC_ID_HAP               , ""     } ,
  { AV_CODEC_ID_DDS               , ""     } ,
  { AV_CODEC_ID_DXV               , ""     } ,
  { AV_CODEC_ID_SCREENPRESSO      , ""     } ,
  { AV_CODEC_ID_RSCC              , ""     } ,
  { 0                             , NULL   }
}                                            ;

QStringList FFmpeg::VideoExtensions(void)
{
  QStringList S                                      ;
  VideoExt  * e = EXTs                               ;
  while ( 0 != e -> codec )                          {
    QString s = QString::fromUtf8 ( e -> extension ) ;
    if ( s . length ( ) > 0 )                        {
      if ( ! S . contains ( s ) ) S << s             ;
    }                                                ;
    e ++                                             ;
  }                                                  ;
  return S                                           ;
}
