/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : gstsmecodecmap.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2014��3��25��
  ����޸�   :
  ��������   : sme ����ת����gst����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��3��25��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __GST_SME_CODECMAP_H__
#define __GST_SME_CODECMAP_H__

#include <gst/gst.h>
#include <gst/audio/audio.h>
#include <gst/video/video.h>

#include "gstsme.h"

#define GST_SME_MIME_MAX_LEN 64

G_BEGIN_DECLS

/*
 * _codecid_to_caps () gets_ the GstCaps that belongs to
 * a certain CodecID for a pad with compressed data.
 */
GstCaps *
gst_sme_codecid_to_caps (E_SME_MEDIA_CODEC_ID codec_id,
	ST_SME_MEDIAINFO * context, gboolean encode);

/*
 * _formatid_to_caps () is meant for muxers/demuxers, it
 * transforms a name (ffmpeg way of ID'ing these, why don't
 * they have unique numerical IDs?) to the corresponding
 * caps belonging to that mux-format
 */
GstCaps *
gst_sme_formatid_to_caps (const gchar * format_name);

GstCaps *
gst_sme_vid_caps_new (ST_SME_MEDIAINFO * context, E_SME_MEDIA_CODEC_ID codec_id,
    const char *mimetype, const char *fieldname, ...);

gboolean
gst_sme_caps_to_videoinfo (const GstCaps * caps, ST_SME_VIDEOINFO* pstVideoInfo, gboolean* bEs);

gboolean
gst_sme_caps_to_audioinfo (const GstCaps * caps, ST_SME_AUDIOINFO* pstAudioInfo, gboolean* bEs);

/*
E_SME_AUDIO_RAW_FMT
gst_sme_caps_to_smpfmt (const GstCaps * caps);
*/

gint
sme_smp_format_to_depth (E_SME_AUDIO_RAW_FMT samplefmt);

GstCaps *
gst_sme_codectype_to_audio_caps (E_SME_MEDIA_CODEC_ID codec_id, ST_SME_MEDIAINFO * context,
                                 gboolean encode,E_SME_AUDIO_RAW_FMT *samplefmts);

G_END_DECLS



#endif /* __GST_SME_CODECMAP_H__ */
