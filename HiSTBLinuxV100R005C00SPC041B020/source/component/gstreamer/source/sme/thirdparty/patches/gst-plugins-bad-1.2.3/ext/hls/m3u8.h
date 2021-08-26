/* GStreamer
 * Copyright (C) 2010 Marc-Andre Lureau <marcandre.lureau@gmail.com>
 * Copyright (C) 2010 Andoni Morales Alastruey <ylatuya@gmail.com>
 *
 * m3u8.h:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __M3U8_H__
#define __M3U8_H__

#include <glib.h>

G_BEGIN_DECLS typedef struct _GstM3U8 GstM3U8;
typedef struct _GstM3U8MediaFile GstM3U8MediaFile;
typedef struct _GstM3U8Client GstM3U8Client;
typedef struct _GstM3U8RenditionGroup GstM3U8RenditionGroup;

#define GST_M3U8(m) ((GstM3U8*)m)
#define GST_M3U8_MEDIA_FILE(f) ((GstM3U8MediaFile*)f)

#define GST_M3U8_CLIENT_LOCK(c) g_mutex_lock (c->lock);
#define GST_M3U8_CLIENT_UNLOCK(c) g_mutex_unlock (c->lock);
#define MAX_SEQUENCE 999999999

struct _GstM3U8RenditionGroup
{
  gchar *type;
  gchar *group_id;
  GList *lists;
};

struct _GstM3U8
{
  gchar *uri;                   /* actually downloaded URI */
  gchar *base_uri;              /* URI to use as base for resolving relative URIs.
                                 * This will be different to uri in case of redirects */
  gchar *name;                  /* This will be the "name" of the playlist, the original
                                 * relative/absolute uri in a variant playlist */

  gboolean endlist;             /* if ENDLIST has been reached */
  gint version;                 /* last EXT-X-VERSION */
  GstClockTime targetduration;  /* last EXT-X-TARGETDURATION */
  gchar *allowcache;            /* last EXT-X-ALLOWCACHE */

  gint bandwidth;
  gint program_id;
  gchar *codecs;
  gint width;
  gint height;
  gboolean iframe;
  GList *files;

  /*< private > */
  gchar *last_data;
  GList *lists;                 /* list of GstM3U8 from the main playlist */
  GList *iframe_lists;          /* I-frame lists from the main playlist */
  GList *current_variant;       /* current variant playlist used */
  GstM3U8 *parent;              /* main playlist (if any) */
  gint filesequence;           /* increased with new media file */

  gint mediasequence;          /* EXT-X-MEDIA-SEQUENCE */
  gboolean mediaseq_flag;

  /* BEGIN: Modified for DTS2015072200692 by lizimian(l00251625), 2015/7/25 */
  /* properties for version 4 */
  /* for main playlist only */
  GstM3U8RenditionGroup *group_audio;

  /* for EXT-X-STREAM-INFO contains multi audio rendition */
  gchar *audio_group_id;

  /* for EXT-X-STREAM-INFO contains audio info only */
  gboolean audio_info;
  gchar *default_audio_uri;

  /* for EXT-X-MEDIA */
  gchar *type;
  gchar *group_id;
  gboolean deft;
  gboolean autoselect;
  gchar *language;
  gchar *language_name;

  /* for EXT-X-PLAYLIST-TYPE */
  gchar *playtype;
  /* BEGIN: Modified for DTS2015072200692 by lizimian(l00251625), 2015/7/25 */

  /* BEGIN: Modified for DTS2015081807240 by wanghua(w00347020), 2015/8/19 */
  /* for EXT-X-PROGRAM-DATE-TIME */
  gchar *program_date_time;
  /* END: Modified for DTS2015081807240 by wanghua(w00347020), 2015/8/19 */

  gboolean iframe_only;      /* EXT-X-I-FRAMES-ONLY */
  gboolean video;            /* EXT-X-STREAM-INF/EXT-X-I-FRAMES-ONLY : VIDEO*/
};

struct _GstM3U8MediaFile
{
  gchar *title;
  GstClockTime duration;
  gchar *uri;
  gint sequence;                /* the sequence nb of this file */
  gboolean discont;             /* this file marks a discontinuity */
  gchar *key;
  guint8 iv[16];
  gchar *print_iv;
  gint64 offset, size;
  gchar *method;
};

struct _GstM3U8Client
{
  GstM3U8 *main;                /* main playlist */
  GstM3U8 *current;
  guint update_failed_count;
  gint sequence;                /* the next sequence for this client */
  GMutex *lock;

  /* properties for version 4 */
  GstM3U8 *current_audio;
  gint sequence_audio;

  /* BEGIN: Modified for DTS2015081807636 by wanghua(w00347020), 2015/8/20 */
  gint first_fragment_sequence;
  /* END: Modified for DTS2015081807636 by wanghua(w00347020), 2015/8/20 */

  /* BEGIN: Modified for DTS2015110206627 by lizimian(l00251625), 2015/11/2 */
  GstClockTime duration_video;
  GstClockTime duration_audio;
  /* END: Modified for DTS2015110206627 by lizimian(l00251625), 2015/11/2 */
};


GstM3U8Client *gst_m3u8_client_new (const gchar * uri, const gchar * base_uri);
void gst_m3u8_client_free (GstM3U8Client * client);
gboolean gst_m3u8_client_update (GstM3U8Client * client, gchar * data, gboolean video);
void gst_m3u8_client_set_current (GstM3U8Client * client, GstM3U8 * m3u8, gboolean video);
gboolean gst_m3u8_client_get_next_fragment (GstM3U8Client * client,
    gboolean * discontinuity, gchar ** uri, GstClockTime * duration,
    GstClockTime * timestamp, gint64 * range_start, gint64 * range_end,
    gchar ** key, guint8 ** iv, gboolean forward, gboolean video);
void gst_m3u8_client_get_current_position (const GstM3U8Client * client,
    GstClockTime * timestamp, gboolean video);
GstClockTime gst_m3u8_client_get_duration (const GstM3U8Client * client, gboolean video);
GstClockTime gst_m3u8_client_get_target_duration (const GstM3U8Client * client, gboolean video);
const gchar *gst_m3u8_client_get_uri(const GstM3U8Client * client);
const gchar *gst_m3u8_client_get_current_uri(const GstM3U8Client * client, gboolean video);
gboolean gst_m3u8_client_has_variant_playlist(const GstM3U8Client * client);
gboolean gst_m3u8_client_is_live(const GstM3U8Client * client);
/* BEGIN: Added for DTS2016042509776, 2016/4/27 */
GList * gst_m3u8_client_get_playlist_for_bitrate (const GstM3U8Client * client,
    guint64 bitrate, gboolean video);
/* END: Added for DTS2016042509776, 2016/4/27 */
gboolean _find_max_sequence (const GstM3U8MediaFile * file, gint max_sequence);

G_END_DECLS
#endif /* __M3U8_H__ */
