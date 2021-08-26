/* GStreamer
 * Copyright (C) 2006 Edward Hervey <edward@fluendo.com>
 * Copyright (C) 2007 Jan Schmidt <jan@fluendo.com>
 * Copyright (C) 2007 Wim Taymans <wim@fluendo.com>
 * Copyright (C) 2011 Sebastian Dröge <sebastian.droege@collabora.co.uk>
 *
 * gstmultiqueue.c:
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

/**
 * SECTION:element-multiqueue
 * @see_also: #GstQueue
 *
 * <refsect2>
 * <para>
 * Multiqueue is similar to a normal #GstQueue with the following additional
 * features:
 * <orderedlist>
 * <listitem>
 *   <itemizedlist><title>Multiple streamhandling</title>
 *   <listitem><para>
 *     The element handles queueing data on more than one stream at once. To
 *     achieve such a feature it has request sink pads (sink&percnt;d) and
 *     'sometimes' src pads (src&percnt;d).
 *   </para><para>
 *     When requesting a given sinkpad with gst_element_get_request_pad(),
 *     the associated srcpad for that stream will be created.
 *     Example: requesting sink1 will generate src1.
 *   </para></listitem>
 *   </itemizedlist>
 * </listitem>
 * <listitem>
 *   <itemizedlist><title>Non-starvation on multiple streams</title>
 *   <listitem><para>
 *     If more than one stream is used with the element, the streams' queues
 *     will be dynamically grown (up to a limit), in order to ensure that no
 *     stream is risking data starvation. This guarantees that at any given
 *     time there are at least N bytes queued and available for each individual
 *     stream.
 *   </para><para>
 *     If an EOS event comes through a srcpad, the associated queue will be
 *     considered as 'not-empty' in the queue-size-growing algorithm.
 *   </para></listitem>
 *   </itemizedlist>
 * </listitem>
 * <listitem>
 *   <itemizedlist><title>Non-linked srcpads graceful handling</title>
 *   <listitem><para>
 *     In order to better support dynamic switching between streams, the multiqueue
 *     (unlike the current GStreamer queue) continues to push buffers on non-linked
 *     pads rather than shutting down.
 *   </para><para>
 *     In addition, to prevent a non-linked stream from very quickly consuming all
 *     available buffers and thus 'racing ahead' of the other streams, the element
 *     must ensure that buffers and inlined events for a non-linked stream are pushed
 *     in the same order as they were received, relative to the other streams
 *     controlled by the element. This means that a buffer cannot be pushed to a
 *     non-linked pad any sooner than buffers in any other stream which were received
 *     before it.
 *   </para></listitem>
 *   </itemizedlist>
 * </listitem>
 * </orderedlist>
 * </para>
 * <para>
 *   Data is queued until one of the limits specified by the
 *   #GstMultiQueue:max-size-buffers, #GstMultiQueue:max-size-bytes and/or
 *   #GstMultiQueue:max-size-time properties has been reached. Any attempt to push
 *   more buffers into the queue will block the pushing thread until more space
 *   becomes available. #GstMultiQueue:extra-size-buffers,
 * </para>
 * <para>
 *   #GstMultiQueue:extra-size-bytes and #GstMultiQueue:extra-size-time are
 *   currently unused.
 * </para>
 * <para>
 *   The default queue size limits are 5 buffers, 10MB of data, or
 *   two second worth of data, whichever is reached first. Note that the number
 *   of buffers will dynamically grow depending on the fill level of
 *   other queues.
 * </para>
 * <para>
 *   The #GstMultiQueue::underrun signal is emitted when all of the queues
 *   are empty. The #GstMultiQueue::overrun signal is emitted when one of the
 *   queues is filled.
 *   Both signals are emitted from the context of the streaming thread.
 * </para>
 * </refsect2>
 *
 * Last reviewed on 2008-01-25 (0.10.17)
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gst/gst.h>
#include <stdio.h>
#include "gstmultiqueue.h"
#include <gst/glib-compat-private.h>

/* Macros definition */
#define GST_SME_DATA_Q_LOW_LVL   0.25
#define GST_SME_DATA_Q_HIGH_LVL  0.75

/* Signals definition */
typedef enum
{
   SIGNAL_OVERRUN,
   SIGNAL_UNDERRUN,
   SIGNAL_NORMALISING,
   SIGNAL_LAST
} GstSmeQueueSignal;

/* QueueStatus definition */
typedef enum
{
   GST_SME_UNDERRUN,
   GST_SME_OVERRUN,
   GST_SME_NORMAL,
   GST_SME_LAST
} GstSmeQueueStatus;

/* Single Queue type */
typedef enum
{
   SQ_T_UNKOWN,
   SQ_T_VIDEO,
   SQ_T_AUDIO,
   SQ_T_TEXT,
   SQ_T_LAST
} GstSmeSingleQueueType;
/**
 * GstSingleQueue:
 * @sinkpad: associated sink #GstPad
 * @srcpad: associated source #GstPad
 *
 * Structure containing all information and properties about
 * a single queue.
 */
typedef struct _GstSingleQueue GstSingleQueue;

struct _GstSingleQueue
{
  /* unique identifier of the queue */
  guint id;

  GstMultiQueue *mqueue;

  GstPad *sinkpad;
  GstPad *srcpad;

  /* flowreturn of previous srcpad push */
  GstFlowReturn srcresult;
  /* If something was actually pushed on
   * this pad after flushing/pad activation
   * and the srcresult corresponds to something
   * real
   */
  gboolean pushed;

  /* segments */
  GstSegment sink_segment;
  GstSegment src_segment;

  /* position of src/sink */
  GstClockTime sinktime, srctime;
  /* TRUE if either position needs to be recalculated */
  gboolean sink_tainted, src_tainted;

  /* queue of data */
  GstDataQueue *queue;
  GstDataQueueSize max_size, extra_size;
  GstClockTime cur_time;
  gboolean is_eos;
  gboolean flushing;
  gint percent;
  guint64 last_pts;              /*The pts of the last buffer*/
  guint64 last_post_time;//ms
  guint64 last_post_avinfo_time;

  /* Protected by global lock */
  guint32 nextid;               /* ID of the next object waiting to be pushed */
  guint32 oldid;                /* ID of the last object pushed (last in a series) */
  guint32 last_oldid;           /* Previously observed old_id, reset to MAXUINT32 on flush */
  GstClockTime next_time;       /* End running time of next buffer to be pushed */
  GstClockTime last_time;       /* Start running time of last pushed buffer */
  GCond turn;                   /* SingleQueue turn waiting conditional */

  /* for serialized queries */
  GCond query_handled;
  gboolean last_query;
  gboolean data_cames;          //if data comes it will set to TRUE, if one of the sq is overrun
                                // but others not cames. then it will push an eos event downstream
  gboolean is_active;           /* indicate if the signle queue is active */
  gboolean active_transiting;   /* indicate if single queue is deactivating */
  gboolean active_flushing;     /* indiecate if the flush is due to activating*/

  /*queue status : overrun, underrun */
  GstSmeSingleQueueType  sq_type;
  GstSmeQueueStatus status;
};


/* Extension of GstDataQueueItem structure for our usage */
typedef struct _GstMultiQueueItem GstMultiQueueItem;

struct _GstMultiQueueItem
{
  GstMiniObject *object;
  guint size;
  guint64 duration;
  gboolean visible;

  GDestroyNotify destroy;
  guint32 posid;

  gboolean is_query;
};

static GstSingleQueue *gst_single_queue_new (GstMultiQueue * mqueue, guint id);
static void gst_single_queue_free (GstSingleQueue * squeue);

static void wake_up_next_non_linked (GstMultiQueue * mq);
static void compute_high_id (GstMultiQueue * mq);
static void compute_high_time (GstMultiQueue * mq);
static gint get_lowest_percent (GstMultiQueue * mq);
static void single_queue_overrun_cb (GstDataQueue * dq, GstSingleQueue * sq);
static void single_queue_underrun_cb (GstDataQueue * dq, GstSingleQueue * sq);

static void gst_single_queue_flush_queue (GstSingleQueue * sq, gboolean full);
static void post_all_buffers_message(GstMultiQueue * mq, GstSingleQueue * sq);

static GstStaticPadTemplate sinktemplate = GST_STATIC_PAD_TEMPLATE ("sink_%u",
    GST_PAD_SINK,
    GST_PAD_REQUEST,
    GST_STATIC_CAPS_ANY);

static GstStaticPadTemplate srctemplate = GST_STATIC_PAD_TEMPLATE ("src_%u",
    GST_PAD_SRC,
    GST_PAD_SOMETIMES,
    GST_STATIC_CAPS_ANY);

GST_DEBUG_CATEGORY_STATIC (multi_queue_debug);
#define GST_CAT_DEFAULT (multi_queue_debug)

/* default limits, we try to keep up to 2 seconds of data and if there is not
 * time, up to 10 MB. The number of buffers is dynamically scaled to make sure
 * there is data in the queues. Normally, the byte and time limits are not hit
 * in theses conditions. */
#define DEFAULT_MAX_SIZE_BYTES 10 * 1024 * 1024 /* 10 MB */
#define DEFAULT_MAX_SIZE_BUFFERS 5
#define DEFAULT_MAX_SIZE_TIME 2 * GST_SECOND

/* second limits. When we hit one of the above limits we are probably dealing
 * with a badly muxed file and we scale the limits to these emergency values.
 * This is currently not yet implemented.
 * Since we dynamically scale the queue buffer size up to the limits but avoid
 * going above the max-size-buffers when we can, we don't really need this
 * aditional extra size. */
#define DEFAULT_EXTRA_SIZE_BYTES 10 * 1024 * 1024       /* 10 MB */
#define DEFAULT_EXTRA_SIZE_BUFFERS 5
#define DEFAULT_EXTRA_SIZE_TIME 3 * GST_SECOND

#define DEFAULT_USE_BUFFERING FALSE
#define DEFAULT_LOW_PERCENT   10
#define DEFAULT_HIGH_PERCENT  99
#define DEFAULT_SYNC_BY_RUNNING_TIME FALSE

enum
{
  PROP_0,
  PROP_EXTRA_SIZE_BYTES,
  PROP_EXTRA_SIZE_BUFFERS,
  PROP_EXTRA_SIZE_TIME,
  PROP_MAX_SIZE_BYTES,
  PROP_MAX_SIZE_BUFFERS,
  PROP_MAX_SIZE_TIME,
  PROP_USE_BUFFERING,
  PROP_LOW_PERCENT,
  PROP_HIGH_PERCENT,
  PROP_SYNC_BY_RUNNING_TIME,
  PROP_CURRENT_PERCENT,
  PROP_ACTIVE_AUDIO_PAD,
  PROP_MQ_IS_AFTER_DEMUX,
  PROP_LAST
};

#define GST_MULTI_QUEUE_MUTEX_LOCK(q) G_STMT_START {                    \
  GST_LOG_OBJECT (q, "lock");                                           \
  g_mutex_lock (&q->qlock);                                             \
  GST_LOG_OBJECT (q, "got lock");                                       \
} G_STMT_END

#define GST_MULTI_QUEUE_MUTEX_UNLOCK(q) G_STMT_START {                  \
  g_mutex_unlock (&q->qlock);                                           \
  GST_LOG_OBJECT (q, "unlock");                                         \
} G_STMT_END

#define GST_MULTI_QUEUE_WAIT(q) G_STMT_START {  \
  g_cond_wait (&(q->cond), &(q->qlock));        \
} G_STMT_END

#define GST_MULTI_QUEUE_BROADCAST(q) G_STMT_START {     \
  g_cond_broadcast (&(q->cond));                        \
} G_STMT_END

static void gst_multi_queue_finalize (GObject * object);
static void gst_multi_queue_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_multi_queue_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec);

static GstPad *gst_multi_queue_request_new_pad (GstElement * element,
    GstPadTemplate * temp, const gchar * name, const GstCaps * caps);
static void gst_multi_queue_release_pad (GstElement * element, GstPad * pad);
static GstStateChangeReturn gst_multi_queue_change_state (GstElement *
    element, GstStateChange transition);

static void gst_multi_queue_loop (GstPad * pad);

static gboolean select_audio_track (GstMultiQueue * mq, GstPad *pad);
static gboolean
activate_audio_track(GstMultiQueue *mq, GstSingleQueue *sq, gboolean active);
static gboolean
gst_single_queue_wait_running_time(GstMultiQueue *mq,
    GstSingleQueue *sq,
    GstBuffer *buf);
static gboolean flush_transiting_audio_track(GstMultiQueue *mq,
    GstSingleQueue *sq);

#define _do_init \
  GST_DEBUG_CATEGORY_INIT (multi_queue_debug, "multiqueue", 0, "multiqueue element");
#define gst_multi_queue_parent_class parent_class
G_DEFINE_TYPE_WITH_CODE (GstMultiQueue, gst_multi_queue, GST_TYPE_ELEMENT,
    _do_init);

static guint gst_multi_queue_signals[SIGNAL_LAST] = { 0 };

#ifdef __SME_MQ_CTRL__
#define SME_POST_INTERVAL 50//ms
static guint64 gst_get_cur_sys_time()
{
    GTimeVal timeval;
    guint64 timetick = 0;

    g_get_current_time (&timeval);

    timetick = (guint64)timeval.tv_sec * 1000 +
        (timeval.tv_usec + 500) / 1000;

    return timetick;
}
#endif

static void
gst_multi_queue_class_init (GstMultiQueueClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (klass);

  gobject_class->set_property = gst_multi_queue_set_property;
  gobject_class->get_property = gst_multi_queue_get_property;

  /* SIGNALS */

  /**
   * GstMultiQueue::underrun:
   * @multiqueue: the multqueue instance
   *
   * This signal is emitted from the streaming thread when there is
   * no data in any of the queues inside the multiqueue instance (underrun).
   *
   * This indicates either starvation or EOS from the upstream data sources.
   */
  gst_multi_queue_signals[SIGNAL_UNDERRUN] =
      g_signal_new ("underrun", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_FIRST,
      G_STRUCT_OFFSET (GstMultiQueueClass, underrun), NULL, NULL,
      g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

  /**
   * GstMultiQueue::overrun:
   * @multiqueue: the multiqueue instance
   *
   * Reports that one of the queues in the multiqueue is full (overrun).
   * A queue is full if the total amount of data inside it (num-buffers, time,
   * size) is higher than the boundary values which can be set through the
   * GObject properties.
   *
   * This can be used as an indicator of pre-roll.
   */
  gst_multi_queue_signals[SIGNAL_OVERRUN] =
      g_signal_new ("overrun", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_FIRST,
      G_STRUCT_OFFSET (GstMultiQueueClass, overrun), NULL, NULL,
      g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

  /**
   * GstMultiQueue::normal:
   * @multiqueue: the multiqueue instance
   *
   * Reports that one of the queues in the multiqueue is full (overrun).
   * A queue is full if the total amount of data inside it (num-buffers, time,
   * size) is higher than the boundary values which can be set through the
   * GObject properties.
   *
   * This can be used as an indicator of pre-roll.
   */
  gst_multi_queue_signals[SIGNAL_NORMALISING] =
      g_signal_new ("normalising", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_FIRST,
      G_STRUCT_OFFSET (GstMultiQueueClass, normalising), NULL, NULL,
      g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

  /* PROPERTIES */

  g_object_class_install_property (gobject_class, PROP_MAX_SIZE_BYTES,
      g_param_spec_uint ("max-size-bytes", "Max. size (kB)",
          "Max. amount of data in the queue (bytes, 0=disable)",
          0, G_MAXUINT, DEFAULT_MAX_SIZE_BYTES,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_MAX_SIZE_BUFFERS,
      g_param_spec_uint ("max-size-buffers", "Max. size (buffers)",
          "Max. number of buffers in the queue (0=disable)", 0, G_MAXUINT,
          DEFAULT_MAX_SIZE_BUFFERS,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_MAX_SIZE_TIME,
      g_param_spec_uint64 ("max-size-time", "Max. size (ns)",
          "Max. amount of data in the queue (in ns, 0=disable)", 0, G_MAXUINT64,
          DEFAULT_MAX_SIZE_TIME, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_EXTRA_SIZE_BYTES,
      g_param_spec_uint ("extra-size-bytes", "Extra Size (kB)",
          "Amount of data the queues can grow if one of them is empty (bytes, 0=disable)"
          " (NOT IMPLEMENTED)",
          0, G_MAXUINT, DEFAULT_EXTRA_SIZE_BYTES,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_EXTRA_SIZE_BUFFERS,
      g_param_spec_uint ("extra-size-buffers", "Extra Size (buffers)",
          "Amount of buffers the queues can grow if one of them is empty (0=disable)"
          " (NOT IMPLEMENTED)",
          0, G_MAXUINT, DEFAULT_EXTRA_SIZE_BUFFERS,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_EXTRA_SIZE_TIME,
      g_param_spec_uint64 ("extra-size-time", "Extra Size (ns)",
          "Amount of time the queues can grow if one of them is empty (in ns, 0=disable)"
          " (NOT IMPLEMENTED)",
          0, G_MAXUINT64, DEFAULT_EXTRA_SIZE_TIME,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  /**
   * GstMultiQueue:use-buffering
   *
   * Enable the buffering option in multiqueue so that BUFFERING messages are
   * emited based on low-/high-percent thresholds.
   */
  g_object_class_install_property (gobject_class, PROP_USE_BUFFERING,
      g_param_spec_boolean ("use-buffering", "Use buffering",
          "Emit GST_MESSAGE_BUFFERING based on low-/high-percent thresholds",
          DEFAULT_USE_BUFFERING, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  /**
   * GstMultiQueue:low-percent
   *
   * Low threshold percent for buffering to start.
   */
  g_object_class_install_property (gobject_class, PROP_LOW_PERCENT,
      g_param_spec_int ("low-percent", "Low percent",
          "Low threshold for buffering to start", 0, 100,
          DEFAULT_LOW_PERCENT, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  /**
   * GstMultiQueue:high-percent
   *
   * High threshold percent for buffering to finish.
   */
  g_object_class_install_property (gobject_class, PROP_HIGH_PERCENT,
      g_param_spec_int ("high-percent", "High percent",
          "High threshold for buffering to finish", 0, 100,
          DEFAULT_HIGH_PERCENT, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  /**
   * GstMultiQueue:current-percent
   *
   * current percent of buffering.
   */
  g_object_class_install_property (gobject_class, PROP_CURRENT_PERCENT,
      g_param_spec_int ("current-percent", "Current percent",
          "Current percent of buffering", 0, 100,
          0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  /**
   * GstMultiQueue:sync-by-running-time
   *
   * If enabled multiqueue will synchronize deactivated or not-linked streams
   * to the activated and linked streams by taking the running time.
   * Otherwise multiqueue will synchronize the deactivated or not-linked
   * streams by keeping the order in which buffers and events arrived compared
   * to active and linked streams.
   */
  g_object_class_install_property (gobject_class, PROP_SYNC_BY_RUNNING_TIME,
      g_param_spec_boolean ("sync-by-running-time", "Sync By Running Time",
          "Synchronize deactivated or not-linked streams by running time",
          DEFAULT_SYNC_BY_RUNNING_TIME,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  /**
   * GstURIDecodeBin::active-pad
   *
   * Select the active pad in the case of multiple tracks
   *
   */
  g_object_class_install_property (gobject_class, PROP_ACTIVE_AUDIO_PAD,
      g_param_spec_object ("active-audio-pad", "Active audio pad",
          "The currently active audio sink pad", GST_TYPE_PAD,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_MQ_IS_AFTER_DEMUX,
      g_param_spec_int ("mq-is-after-demux", "is_after_demux",
          "is_after_demux", 0, G_MAXINT,
          1, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gobject_class->finalize = gst_multi_queue_finalize;

  gst_element_class_set_static_metadata (gstelement_class,
      "MultiQueue",
      "Generic", "Multiple data queue", "Edward Hervey <edward@fluendo.com>");
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sinktemplate));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&srctemplate));

  gstelement_class->request_new_pad =
      GST_DEBUG_FUNCPTR (gst_multi_queue_request_new_pad);
  gstelement_class->release_pad =
      GST_DEBUG_FUNCPTR (gst_multi_queue_release_pad);
  gstelement_class->change_state =
      GST_DEBUG_FUNCPTR (gst_multi_queue_change_state);
}

static void
gst_multi_queue_init (GstMultiQueue * mqueue)
{
  mqueue->nbqueues = 0;
  mqueue->queues = NULL;

  mqueue->max_size.bytes = DEFAULT_MAX_SIZE_BYTES;
  mqueue->max_size.visible = DEFAULT_MAX_SIZE_BUFFERS;
  mqueue->max_size.time = DEFAULT_MAX_SIZE_TIME;

  mqueue->extra_size.bytes = DEFAULT_EXTRA_SIZE_BYTES;
  mqueue->extra_size.visible = DEFAULT_EXTRA_SIZE_BUFFERS;
  mqueue->extra_size.time = DEFAULT_EXTRA_SIZE_TIME;

  mqueue->use_buffering = DEFAULT_USE_BUFFERING;
  mqueue->low_percent = DEFAULT_LOW_PERCENT;
  mqueue->high_percent = DEFAULT_HIGH_PERCENT;

  mqueue->sync_by_running_time = DEFAULT_SYNC_BY_RUNNING_TIME;

  mqueue->counter = 1;
  mqueue->highid = -1;
  mqueue->high_time = GST_CLOCK_TIME_NONE;

  g_mutex_init (&mqueue->qlock);
  g_cond_init (&mqueue->cond);
#ifdef __SME_MQ_CTRL__
  mqueue->buffering = TRUE;
  mqueue->last_post_time = GST_CLOCK_TIME_NONE;
  mqueue->last_percent = 0;
#endif
  mqueue->is_after_demux = 1;
  mqueue->use_max_time_check_buffer_full = TRUE;
}

static void
gst_multi_queue_finalize (GObject * object)
{
  GstMultiQueue *mqueue = GST_MULTI_QUEUE (object);

  g_list_foreach (mqueue->queues, (GFunc) gst_single_queue_free, NULL);
  g_list_free (mqueue->queues);
  mqueue->queues = NULL;
  mqueue->queues_cookie++;

  /* free/unref instance data */
  g_mutex_clear (&mqueue->qlock);
  g_cond_clear (&mqueue->cond);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

#define SET_CHILD_PROPERTY(mq,format) G_STMT_START {	        \
    GList * tmp = mq->queues;					\
    while (tmp) {						\
      GstSingleQueue *q = (GstSingleQueue*)tmp->data;		\
      q->max_size.format = mq->max_size.format;                 \
      tmp = g_list_next(tmp);					\
    };								\
} G_STMT_END

static void
gst_multi_queue_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstMultiQueue *mq = GST_MULTI_QUEUE (object);

  switch (prop_id) {
    case PROP_MAX_SIZE_BYTES:
      GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      mq->max_size.bytes = g_value_get_uint (value);
      GST_INFO("gst_multi_queue_set_property mq->max_size.bytes=%d", mq->max_size.bytes);
      SET_CHILD_PROPERTY (mq, bytes);
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      break;
    case PROP_MAX_SIZE_BUFFERS:
    {
      GList *tmp;
      gint new_size = g_value_get_uint (value);

      GST_MULTI_QUEUE_MUTEX_LOCK (mq);

      tmp = mq->queues;
      while (tmp) {
        GstDataQueueSize size;
        GstSingleQueue *q = (GstSingleQueue *) tmp->data;
        gst_data_queue_get_level (q->queue, &size);

        /* do not reduce max size below current level if the single queue has grown because of empty queue */
        if (new_size == 0) {
          q->max_size.visible = new_size;
        } else if (new_size > size.visible) {
          q->max_size.visible = new_size;
        }
        tmp = g_list_next (tmp);
      };

      mq->max_size.visible = new_size;

      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

      break;
    }
    case PROP_MQ_IS_AFTER_DEMUX:
      mq->is_after_demux = g_value_get_int(value);
      GST_INFO("cur mq:%p,mq->is_after_demux=%d", mq, mq->is_after_demux);
      break;
    case PROP_MAX_SIZE_TIME:
      GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      mq->max_size.time = g_value_get_uint64 (value);
      SET_CHILD_PROPERTY (mq, time);
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      break;
    case PROP_EXTRA_SIZE_BYTES:
      mq->extra_size.bytes = g_value_get_uint (value);
      break;
    case PROP_EXTRA_SIZE_BUFFERS:
      mq->extra_size.visible = g_value_get_uint (value);
      break;
    case PROP_EXTRA_SIZE_TIME:
      mq->extra_size.time = g_value_get_uint64 (value);
      break;
    case PROP_USE_BUFFERING:
      mq->use_buffering = g_value_get_boolean (value);
      break;
    case PROP_LOW_PERCENT:
      mq->low_percent = g_value_get_int (value);
      break;
    case PROP_HIGH_PERCENT:
      mq->high_percent = g_value_get_int (value);
      break;
    case PROP_SYNC_BY_RUNNING_TIME:
      mq->sync_by_running_time = g_value_get_boolean (value);
      break;
     case PROP_ACTIVE_AUDIO_PAD:{
       GstPad *pad, *target;
       GstObject *decodebin;

       pad = g_value_get_object (value);
       GST_INFO_OBJECT (mq, "set active pad %s", GST_PAD_NAME(pad));
       if (pad) {
           select_audio_track (object, pad);
       }
       break;
     }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_multi_queue_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstMultiQueue *mq = GST_MULTI_QUEUE (object);

  switch (prop_id) {
    case PROP_EXTRA_SIZE_BYTES:
      g_value_set_uint (value, mq->extra_size.bytes);
      break;
    case PROP_EXTRA_SIZE_BUFFERS:
      g_value_set_uint (value, mq->extra_size.visible);
      break;
    case PROP_EXTRA_SIZE_TIME:
      g_value_set_uint64 (value, mq->extra_size.time);
      break;
    case PROP_MAX_SIZE_BYTES:
      GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      g_value_set_uint (value, mq->max_size.bytes);
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      break;
    case PROP_MAX_SIZE_BUFFERS:
      GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      g_value_set_uint (value, mq->max_size.visible);
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      break;
    case PROP_MAX_SIZE_TIME:
      GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      g_value_set_uint64 (value, mq->max_size.time);
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      break;
    case PROP_USE_BUFFERING:
      g_value_set_boolean (value, mq->use_buffering);
      break;
    case PROP_LOW_PERCENT:
      g_value_set_int (value, mq->low_percent);
      break;
    case PROP_HIGH_PERCENT:
      g_value_set_int (value, mq->high_percent);
      break;
    case PROP_CURRENT_PERCENT:
      g_value_set_int (value, get_lowest_percent(mq));
      break;
    case PROP_SYNC_BY_RUNNING_TIME:
      g_value_set_boolean (value, mq->sync_by_running_time);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static GstIterator *
gst_multi_queue_iterate_internal_links (GstPad * pad, GstObject * parent)
{
  GstIterator *it = NULL;
  GstPad *opad;
  GstSingleQueue *squeue;
  GstMultiQueue *mq = GST_MULTI_QUEUE (parent);
  GValue val = { 0, };

  GST_MULTI_QUEUE_MUTEX_LOCK (mq);
  squeue = gst_pad_get_element_private (pad);
  if (!squeue)
    goto out;

  if (squeue->sinkpad == pad)
    opad = gst_object_ref (squeue->srcpad);
  else if (squeue->srcpad == pad)
    opad = gst_object_ref (squeue->sinkpad);
  else
    goto out;

  g_value_init (&val, GST_TYPE_PAD);
  g_value_set_object (&val, opad);
  it = gst_iterator_new_single (GST_TYPE_PAD, &val);
  g_value_unset (&val);

  gst_object_unref (opad);

out:
  GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

  return it;
}


/*
 * GstElement methods
 */

static GstPad *
gst_multi_queue_request_new_pad (GstElement * element, GstPadTemplate * temp,
    const gchar * name, const GstCaps * caps)
{
  GstMultiQueue *mqueue = GST_MULTI_QUEUE (element);
  GstSingleQueue *squeue;
  guint temp_id = -1;

  if (name) {
    sscanf (name + 4, "_%u", &temp_id);
    GST_LOG_OBJECT (element, "name : %s (id %d)", GST_STR_NULL (name), temp_id);
  }

  /* Create a new single queue, add the sink and source pad and return the sink pad */
  squeue = gst_single_queue_new (mqueue, temp_id);

  GST_DEBUG_OBJECT (mqueue, "Returning pad %s:%s",
      GST_DEBUG_PAD_NAME (squeue->sinkpad));

  return squeue ? squeue->sinkpad : NULL;
}

static void
gst_multi_queue_release_pad (GstElement * element, GstPad * pad)
{
  GstMultiQueue *mqueue = GST_MULTI_QUEUE (element);
  GstSingleQueue *sq = NULL;
  GList *tmp;

  GST_LOG_OBJECT (element, "pad %s:%s", GST_DEBUG_PAD_NAME (pad));

  GST_MULTI_QUEUE_MUTEX_LOCK (mqueue);
  /* Find which single queue it belongs to, knowing that it should be a sinkpad */
  for (tmp = mqueue->queues; tmp; tmp = g_list_next (tmp)) {
    sq = (GstSingleQueue *) tmp->data;

    if (sq->sinkpad == pad)
      break;
  }

  if (!tmp) {
    GST_WARNING_OBJECT (mqueue, "That pad doesn't belong to this element ???");
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mqueue);
    return;
  }

  /* FIXME: The removal of the singlequeue should probably not happen until it
   * finishes draining */

  /* remove it from the list */
  mqueue->queues = g_list_delete_link (mqueue->queues, tmp);
  mqueue->queues_cookie++;

  /* FIXME : recompute next-non-linked */
  GST_MULTI_QUEUE_MUTEX_UNLOCK (mqueue);

  /* delete SingleQueue */
  gst_data_queue_set_flushing (sq->queue, TRUE);

  gst_pad_set_active (sq->srcpad, FALSE);
  gst_pad_set_active (sq->sinkpad, FALSE);
  gst_pad_set_element_private (sq->srcpad, NULL);
  gst_pad_set_element_private (sq->sinkpad, NULL);
  gst_element_remove_pad (element, sq->srcpad);
  gst_element_remove_pad (element, sq->sinkpad);
  gst_single_queue_free (sq);
}

static GstStateChangeReturn
gst_multi_queue_change_state (GstElement * element, GstStateChange transition)
{
  GstMultiQueue *mqueue = GST_MULTI_QUEUE (element);
  GstSingleQueue *sq = NULL;
  GstStateChangeReturn result;

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:{
      GList *tmp;

      /* Set all pads to non-flushing */
      GST_MULTI_QUEUE_MUTEX_LOCK (mqueue);
      for (tmp = mqueue->queues; tmp; tmp = g_list_next (tmp)) {
        sq = (GstSingleQueue *) tmp->data;
        sq->flushing = FALSE;
      }

      /* the visible limit might not have been set on single queues that have grown because of other queueus were empty */
      SET_CHILD_PROPERTY (mqueue, visible);

      GST_MULTI_QUEUE_MUTEX_UNLOCK (mqueue);

      break;
    }
    case GST_STATE_CHANGE_PAUSED_TO_READY:{
      GList *tmp;

      /* Un-wait all waiting pads */
      GST_MULTI_QUEUE_MUTEX_LOCK (mqueue);
      /* wake up tasks of inactive pads */
      GST_MULTI_QUEUE_BROADCAST(mqueue);
      for (tmp = mqueue->queues; tmp; tmp = g_list_next (tmp)) {
        sq = (GstSingleQueue *) tmp->data;
        sq->flushing = TRUE;
        sq->data_cames = FALSE;
        g_cond_signal (&sq->turn);

        sq->last_query = FALSE;
        g_cond_signal (&sq->query_handled);
      }
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mqueue);
      break;
    }
    default:
      break;
  }

  result = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    default:
      break;
  }

  return result;
}

static gboolean
gst_single_queue_flush (GstMultiQueue * mq, GstSingleQueue * sq, gboolean flush,
    gboolean full)
{
  gboolean result;

  GST_INFO_OBJECT (mq, "flush %s queue %d", (flush ? "start" : "stop"),
      sq->id);

  if (flush) {
    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    sq->srcresult = GST_FLOW_FLUSHING;
    gst_data_queue_set_flushing (sq->queue, TRUE);

    sq->flushing = TRUE;

    /* wake up non-linked task */
    GST_INFO_OBJECT (mq, "SingleQueue %d : waking up eventually waiting task",
        sq->id);
    g_cond_signal (&sq->turn);
    sq->last_query = FALSE;
    g_cond_signal (&sq->query_handled);
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    /* wake up threads waiting on cond */
    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    GST_MULTI_QUEUE_BROADCAST(mq);
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    GST_INFO_OBJECT (mq, "SingleQueue %d : pausing task", sq->id);
    result = gst_pad_pause_task (sq->srcpad);
    GST_INFO_OBJECT (mq, "SingleQueue %d : paused task", sq->id);
    sq->sink_tainted = sq->src_tainted = TRUE;
    /* BEGIN: Added for DTS2015102500281 by liurongliang(l00180035), 2015/10/27 */
    sq->percent = 0;
    sq->last_post_time = GST_CLOCK_TIME_NONE;
    /* END:   Added for DTS2015102500281 by liurongliang(l00180035), 2015/10/27 */
    /** BEGIN: Added for DTS2015102709689 by baihaili(b00311320), 2015/10/27 */
    sq->last_post_avinfo_time = GST_CLOCK_TIME_NONE;
    /* END:   Added for DTS2015102709689 by baihaili(b00311320), 2015/10/27 */
  } else {
    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    gst_single_queue_flush_queue (sq, full);
    gst_segment_init (&sq->sink_segment, GST_FORMAT_TIME);
    gst_segment_init (&sq->src_segment, GST_FORMAT_TIME);
    /* All pads start off not-linked for a smooth kick-off */
    sq->srcresult = GST_FLOW_OK;
    sq->pushed = FALSE;
    sq->cur_time = 0;
    sq->max_size.visible = mq->max_size.visible;
    sq->is_eos = FALSE;
    sq->nextid = 0;
    sq->oldid = 0;
    sq->last_oldid = G_MAXUINT32;
    sq->next_time = GST_CLOCK_TIME_NONE;
    sq->last_time = GST_CLOCK_TIME_NONE;
    gst_data_queue_set_flushing (sq->queue, FALSE);

    /* Reset high time to be recomputed next */
    mq->high_time = GST_CLOCK_TIME_NONE;

    sq->flushing = FALSE;
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    GST_INFO_OBJECT (mq, "SingleQueue %d : starting task", sq->id);
    result =
        gst_pad_start_task (sq->srcpad, (GstTaskFunction) gst_multi_queue_loop,
        sq->srcpad, NULL);
  }
  return result;
}

#if defined (__SME_MQ_CTRL__)
/** Simplified update scheme, which is update percent and statistic message
 * in period without other check.
 */
static void
update_buffering (GstMultiQueue * mq, GstSingleQueue * sq)
{
  GstDataQueueSize size;
  gint percent, tmp;
  gboolean post = FALSE;

  guint64 cur_post_time = 0;

  /* nothing to dowhen we are not in buffering mode */
  if (!mq->use_buffering)
    return;

  gst_data_queue_get_level (sq->queue, &size);

  GST_DEBUG_OBJECT (mq,
      "queue %d: visible %u/%u, bytes %u/%u, time %" G_GUINT64_FORMAT "/%"
      G_GUINT64_FORMAT, sq->id, size.visible, sq->max_size.visible,
      size.bytes, sq->max_size.bytes, sq->cur_time, sq->max_size.time);

  /* get bytes and time percentages and take the max */
  if (sq->is_eos || sq->srcresult == GST_FLOW_NOT_LINKED) {
    percent = 100;
  } else {
    percent = 0;

    if (sq->max_size.time > 0) {
      tmp = (sq->cur_time * 100) / sq->max_size.time;
      sq->percent = MAX (percent, tmp);
    }
    else if (sq->max_size.bytes > 0) {
      tmp = (size.bytes * 100) / sq->max_size.bytes;
      sq->percent = MAX (percent, tmp);
    }
    /** BEGIN: Added for DTS2015082102992 by baihaili(b00311320), 2015/8/29 */
    percent = get_lowest_percent(mq);
    /* END:   Added by baihaili(b00311320), 2015/8/29 */
  }


  if (mq->buffering) {
    post = TRUE;
    if (percent >= 100) {
      mq->buffering = FALSE;
    }

    if (percent == mq->percent)
      /* don't post if nothing changed */
      post = FALSE;
    else
      /* else keep last value we posted */
      mq->percent = percent;
  } else {
  if (percent <= mq->low_percent) {
      mq->buffering = TRUE;
      mq->percent = percent;
      post = TRUE;
    }
  }

  cur_post_time = gst_get_cur_sys_time();
  if(GST_CLOCK_TIME_NONE == sq->last_post_time
    || ((sq->last_post_time + SME_POST_INTERVAL) <= cur_post_time && percent != mq->last_percent)
    || (percent >= 100 && mq->last_percent < 100)
    /** BEGIN: Added for DTS2015082102992 by baihaili(b00311320), 2015/8/29 */
    || (percent == 0 && mq->last_percent != 0)){
    /** END:   Added by baihaili(b00311320), 2015/8/29 */
    post = TRUE;
    sq->last_post_time = cur_post_time;
    //post 100%, 90% not post, 100%(< 50ms) will not post, because last_percent=100
    //and the buffer is full, cannot push data to the queue.
    //so the last 100% will not post to pipeline forever.
    //mq->last_percent = percent;
  }else{
    post = FALSE;
  }

  mq->last_percent = percent;

  if (post) {
    GstMessage *message;

    /* clip */
    if (percent > 100)
      percent = 100;

    GST_DEBUG_OBJECT (mq, "buffering %d percent", percent);
    message = gst_message_new_buffering (GST_OBJECT_CAST (mq), percent);
    gst_element_post_message (GST_ELEMENT_CAST (mq), message);

  } else {
    GST_DEBUG_OBJECT (mq, "filled %d percent", percent);
  }

  /** BEGIN: Added for DTS2015102709689 by baihaili(b00311320), 2015/10/27 */
  if (GST_CLOCK_TIME_NONE == sq->last_post_avinfo_time
      || ((sq->last_post_avinfo_time + SME_POST_INTERVAL) <= cur_post_time)) {
    post_all_buffers_message(mq, sq);
    sq->last_post_avinfo_time = cur_post_time;
  /** END:   Added by baihaili(b00311320), 2015/10/27 */
  }
}

#else
static void
update_buffering (GstMultiQueue * mq, GstSingleQueue * sq)
{
  GstDataQueueSize size;
  gint percent, tmp;
  gboolean post = FALSE;

#ifdef __SME_MQ_CTRL__
  guint64 cur_post_time = 0;
#endif

  /* nothing to dowhen we are not in buffering mode */
  if (!mq->use_buffering)
    return;

  gst_data_queue_get_level (sq->queue, &size);

  GST_DEBUG_OBJECT (mq,
      "queue %d: visible %u/%u, bytes %u/%u, time %" G_GUINT64_FORMAT "/%"
      G_GUINT64_FORMAT, sq->id, size.visible, sq->max_size.visible,
      size.bytes, sq->max_size.bytes, sq->cur_time, sq->max_size.time);

  /* get bytes and time percentages and take the max */
  if (sq->is_eos || sq->srcresult == GST_FLOW_NOT_LINKED) {
    percent = 100;
  } else {
    percent = 0;
#ifdef __SME_MQ_CTRL__
    if (sq->max_size.time > 0) {
      tmp = (sq->cur_time * 100) / sq->max_size.time;
      sq->percent = MAX (percent, tmp);
    }
    else if (sq->max_size.bytes > 0) {
      tmp = (size.bytes * 100) / sq->max_size.bytes;
      sq->percent = MAX (percent, tmp);
    }
    /** BEGIN: Added for DTS2015082102992 by baihaili(b00311320), 2015/8/29 */
    percent = get_lowest_percent(mq);
    /* END:   Added by baihaili(b00311320), 2015/8/29 */
#else
    if (sq->max_size.time > 0) {
      tmp = (sq->cur_time * 100) / sq->max_size.time;
      percent = MAX (percent, tmp);
    }

    if (sq->max_size.bytes > 0) {
      tmp = (size.bytes * 100) / sq->max_size.bytes;
      percent = MAX (percent, tmp);
    }
#endif
  }


  if (mq->buffering) {
    post = TRUE;
#ifndef __SME_MQ_CTRL__
    if (percent >= mq->high_percent) {
      mq->buffering = FALSE;
    }
    /* make sure it increases */
    percent = MAX(mq->percent,percent);
#else
    if (percent >= 100) {
      mq->buffering = FALSE;
    }
#endif

    if (percent == mq->percent)
      /* don't post if nothing changed */
      post = FALSE;
    else
      /* else keep last value we posted */
      mq->percent = percent;
  } else {
#ifdef __SME_MQ_CTRL__
  if (percent <= mq->low_percent) {
#else
    if (percent < mq->low_percent) {
#endif
      mq->buffering = TRUE;
      mq->percent = percent;
      post = TRUE;
    }
  }

#ifdef __SME_MQ_CTRL__
  cur_post_time = gst_get_cur_sys_time();
  if(GST_CLOCK_TIME_NONE == mq->last_post_time
    || ((mq->last_post_time + SME_POST_INTERVAL) <= cur_post_time && percent != mq->last_percent)
    || (percent >= 100 && mq->last_percent < 100)
    /** BEGIN: Added for DTS2015082102992 by baihaili(b00311320), 2015/8/29 */
    || (percent == 0 && mq->last_percent != 0)){
    /** END:   Added by baihaili(b00311320), 2015/8/29 */
    post = TRUE;
    mq->last_post_time = cur_post_time;
    mq->last_percent = percent;
  }else{
    post = FALSE;
  }
#endif

  if (post) {
    GstMessage *message;

#ifndef __SME_MQ_CTRL__
    /* scale to high percent so that it becomes the 100% mark */
    percent = percent * 100 / mq->high_percent;
#endif

    /* clip */
    if (percent > 100)
      percent = 100;

    GST_DEBUG_OBJECT (mq, "buffering %d percent", percent);
    message = gst_message_new_buffering (GST_OBJECT_CAST (mq), percent);

    gst_element_post_message (GST_ELEMENT_CAST (mq), message);
  } else {
    GST_DEBUG_OBJECT (mq, "filled %d percent", percent);
  }
}
#endif
/* calculate the diff between running time on the sink and src of the queue.
 * This is the total amount of time in the queue.
 * WITH LOCK TAKEN */
static void
update_time_level (GstMultiQueue * mq, GstSingleQueue * sq)
{
  gint64 sink_time, src_time;

  if (sq->sink_tainted) {
    sink_time = sq->sinktime =
        gst_segment_to_running_time (&sq->sink_segment, GST_FORMAT_TIME,
        sq->sink_segment.position);

    if (G_UNLIKELY (sink_time != GST_CLOCK_TIME_NONE))
      /* if we have a time, we become untainted and use the time */
      sq->sink_tainted = FALSE;
  } else
    sink_time = sq->sinktime;

  if (sq->src_tainted) {
    src_time = sq->srctime =
        gst_segment_to_running_time (&sq->src_segment, GST_FORMAT_TIME,
        sq->src_segment.position);
    /* if we have a time, we become untainted and use the time */
    if (G_UNLIKELY (src_time != GST_CLOCK_TIME_NONE))
      sq->src_tainted = FALSE;
  } else
    src_time = sq->srctime;

  GST_DEBUG_OBJECT (mq, "queue %d, sink_time:%lld, src_time:%lld", sq->id,
      sink_time, src_time);

  /* This allows for streams with out of order timestamping - sometimes the
   * emerging timestamp is later than the arriving one(s) */
  if (G_LIKELY (sink_time != -1 && src_time != -1 && sink_time > src_time))
    sq->cur_time = sink_time - src_time;
  else
    sq->cur_time = 0;

  /* updating the time level can change the buffering state */
  update_buffering (mq, sq);

  return;
}

/* take a SEGMENT event and apply the values to segment, updating the time
 * level of queue. */
static void
apply_segment (GstMultiQueue * mq, GstSingleQueue * sq, GstEvent * event,
    GstSegment * segment)
{
  gst_event_copy_segment (event, segment);

  /* now configure the values, we use these to track timestamps on the
   * sinkpad. */
  if (segment->format != GST_FORMAT_TIME) {
    /* non-time format, pretent the current time segment is closed with a
     * 0 start and unknown stop time. */
    segment->format = GST_FORMAT_TIME;
    segment->start = 0;
    segment->stop = -1;
    segment->time = 0;
  }
  GST_MULTI_QUEUE_MUTEX_LOCK (mq);

  if (segment == &sq->sink_segment)
    sq->sink_tainted = TRUE;
  else
    sq->src_tainted = TRUE;

  GST_DEBUG_OBJECT (mq,
      "queue %d, configured SEGMENT %" GST_SEGMENT_FORMAT, sq->id, segment);

  /* segment can update the time level of the queue */
  update_time_level (mq, sq);

  GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
}

/* take a buffer and update segment, updating the time level of the queue. */
static void
apply_buffer (GstMultiQueue * mq, GstSingleQueue * sq, GstClockTime timestamp,
    GstClockTime duration, GstSegment * segment)
{
  GST_MULTI_QUEUE_MUTEX_LOCK (mq);

  /* if no timestamp is set, assume it's continuous with the previous
   * time */
  if (timestamp == GST_CLOCK_TIME_NONE)
    timestamp = segment->position;

  /* add duration */
  if (duration != GST_CLOCK_TIME_NONE)
    timestamp += duration;

  GST_DEBUG_OBJECT (mq, "queue %d, position updated to %" GST_TIME_FORMAT,
      sq->id, GST_TIME_ARGS (timestamp));

  segment->position = timestamp;
  GST_DEBUG_OBJECT (mq, "queue %d, position updated to %lld",
      sq->id, timestamp);

  if (segment == &sq->sink_segment)
    sq->sink_tainted = TRUE;
  else
    sq->src_tainted = TRUE;

  /* calc diff with other end */
  update_time_level (mq, sq);
  GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
}

static GstClockTime
get_running_time (GstSegment * segment, GstMiniObject * object, gboolean end)
{
  GstClockTime time = GST_CLOCK_TIME_NONE;

  if (GST_IS_BUFFER (object)) {
    GstBuffer *buf = GST_BUFFER_CAST (object);

    if (GST_BUFFER_TIMESTAMP_IS_VALID (buf)) {
      time = GST_BUFFER_TIMESTAMP (buf);
      if (end && GST_BUFFER_DURATION_IS_VALID (buf))
        time += GST_BUFFER_DURATION (buf);
      if (time > segment->stop)
        time = segment->stop;
      time = gst_segment_to_running_time (segment, GST_FORMAT_TIME, time);
    }
  } else if (GST_IS_BUFFER_LIST (object)) {
    GstBufferList *list = GST_BUFFER_LIST_CAST (object);
    gint i, n;
    GstBuffer *buf;

    n = gst_buffer_list_length (list);
    for (i = 0; i < n; i++) {
      buf = gst_buffer_list_get (list, i);
      if (GST_BUFFER_TIMESTAMP_IS_VALID (buf)) {
        time = GST_BUFFER_TIMESTAMP (buf);
        if (end && GST_BUFFER_DURATION_IS_VALID (buf))
          time += GST_BUFFER_DURATION (buf);
        if (time > segment->stop)
          time = segment->stop;
        time = gst_segment_to_running_time (segment, GST_FORMAT_TIME, time);
        if (!end)
          goto done;
      } else if (!end) {
        goto done;
      }
    }
  } else if (GST_IS_EVENT (object)) {
    GstEvent *event = GST_EVENT_CAST (object);

    /* For newsegment events return the running time of the start position */
    if (GST_EVENT_TYPE (event) == GST_EVENT_SEGMENT) {
      const GstSegment *new_segment;

      gst_event_parse_segment (event, &new_segment);
      if (new_segment->format == GST_FORMAT_TIME) {
        time =
            gst_segment_to_running_time (new_segment, GST_FORMAT_TIME,
            new_segment->start);
      }
    }
  }

done:
  return time;
}

static GstFlowReturn
gst_single_queue_push_one (GstMultiQueue * mq, GstSingleQueue * sq,
    GstMiniObject * object)
{
  GstFlowReturn result = GST_FLOW_OK;

  if (GST_IS_BUFFER (object)) {
    GstBuffer *buffer;
    GstClockTime timestamp, duration;

    buffer = GST_BUFFER_CAST (object);
    /** BEGIN: Added for DTS2015102708085 by baihaili(b00311320), 2015/10/26 */
    if (GST_CLOCK_TIME_NONE != GST_BUFFER_DTS(buffer))
        timestamp = GST_BUFFER_DTS(buffer);
    else
        timestamp = GST_BUFFER_TIMESTAMP(buffer);
    /** END:   Added by baihaili(b00311320), 2015/10/26 */
    duration = GST_BUFFER_DURATION (buffer);

    apply_buffer (mq, sq, timestamp, duration, &sq->src_segment);

    /* Applying the buffer may have made the queue non-full again, unblock it if needed */
    gst_data_queue_limits_changed (sq->queue);

    GST_DEBUG_OBJECT (mq,
        "SingleQueue %d : Pushing buffer %p with ts %" GST_TIME_FORMAT,
        sq->id, buffer, GST_TIME_ARGS (timestamp));

    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    if (!sq->is_active) {
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      GST_DEBUG_OBJECT (mq, "before drop buffer of inactive pad");
      gst_single_queue_wait_running_time (mq, sq, buffer);
      gst_buffer_unref(buffer);
      GST_DEBUG_OBJECT (mq, "drop buffer of inactive pad");
      return result;
    }
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    /* wake up blocked tasks of inactive pad */
    GST_MULTI_QUEUE_BROADCAST(mq);
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    flush_transiting_audio_track (mq, sq);

    result = gst_pad_push (sq->srcpad, buffer);

    GST_MULTI_QUEUE_MUTEX_LOCK(mq);
    if (sq->active_flushing || !sq->is_active) {
        GST_INFO_OBJECT(mq, "pad is in the middle of transition, return ok even"
            " original push result is %s", gst_flow_get_name(result));
      sq->active_flushing = FALSE;
      result = GST_FLOW_OK;
    }
    GST_MULTI_QUEUE_MUTEX_UNLOCK(mq);
  } else if (GST_IS_EVENT (object)) {
    GstEvent *event;

    event = GST_EVENT_CAST (object);

    switch (GST_EVENT_TYPE (event)) {
      case GST_EVENT_EOS:
        result = GST_FLOW_EOS;
        break;
      case GST_EVENT_SEGMENT:
        apply_segment (mq, sq, event, &sq->src_segment);
        /* Applying the segment may have made the queue non-full again, unblock it if needed */
        gst_data_queue_limits_changed (sq->queue);
        break;
      default:
        break;
    }

    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    /* wake up blocked tasks of inactive pad */
    GST_MULTI_QUEUE_BROADCAST(mq);
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    GST_DEBUG_OBJECT (mq,
        "SingleQueue %d : Pushing event %p of type %s",
        sq->id, event, GST_EVENT_TYPE_NAME (event));

    gst_pad_push_event (sq->srcpad, event);
  } else if (GST_IS_QUERY (object)) {
    GstQuery *query;
    gboolean res;

    query = GST_QUERY_CAST (object);

    res = gst_pad_peer_query (sq->srcpad, query);

    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    sq->last_query = res;
    g_cond_signal (&sq->query_handled);
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
  } else {
    g_warning ("Unexpected object in singlequeue %u (refcounting problem?)",
        sq->id);
  }
  return result;

  /* ERRORS */
}

static GstMiniObject *
gst_multi_queue_item_steal_object (GstMultiQueueItem * item)
{
  GstMiniObject *res;

  res = item->object;
  item->object = NULL;

  return res;
}

static void
gst_multi_queue_item_destroy (GstMultiQueueItem * item)
{
  if (!item->is_query && item->object)
    gst_mini_object_unref (item->object);
  g_slice_free (GstMultiQueueItem, item);
}

/* takes ownership of passed mini object! */
static GstMultiQueueItem *
gst_multi_queue_buffer_item_new (GstMiniObject * object, guint32 curid)
{
  GstMultiQueueItem *item;

  item = g_slice_new (GstMultiQueueItem);
  item->object = object;
  item->destroy = (GDestroyNotify) gst_multi_queue_item_destroy;
  item->posid = curid;
  item->is_query = GST_IS_QUERY (object);

  item->size = gst_buffer_get_size (GST_BUFFER_CAST (object));
  item->duration = GST_BUFFER_DURATION (object);
  if (item->duration == GST_CLOCK_TIME_NONE)
    item->duration = 0;
  item->visible = TRUE;
  return item;
}

static GstMultiQueueItem *
gst_multi_queue_mo_item_new (GstMiniObject * object, guint32 curid)
{
  GstMultiQueueItem *item;

  item = g_slice_new (GstMultiQueueItem);
  item->object = object;
  item->destroy = (GDestroyNotify) gst_multi_queue_item_destroy;
  item->posid = curid;
  item->is_query = GST_IS_QUERY (object);

  item->size = 0;
  item->duration = 0;
  item->visible = FALSE;
  return item;
}

/* Each main loop attempts to push buffers until the return value
 * is not-linked. not-linked pads are not allowed to push data beyond
 * any linked pads, so they don't 'rush ahead of the pack'.
 */
static void
gst_multi_queue_loop (GstPad * pad)
{
  GstSingleQueue *sq;
  GstMultiQueueItem *item;
  GstDataQueueItem *sitem;
  GstMultiQueue *mq;
  GstMiniObject *object = NULL;
  guint32 newid;
  GstFlowReturn result;
  GstClockTime next_time;
  gboolean is_buffer;
  gboolean do_update_buffering = FALSE;

  sq = (GstSingleQueue *) gst_pad_get_element_private (pad);
  mq = sq->mqueue;

  GST_DEBUG_OBJECT (mq, "SingleQueue %d : trying to pop an object", sq->id);

  if (sq->flushing)
    goto out_flushing;

  /* Get something from the queue, blocking until that happens, or we get
   * flushed */
  if (!(gst_data_queue_pop (sq->queue, &sitem)))
    goto out_flushing;

  item = (GstMultiQueueItem *) sitem;
  newid = item->posid;

  /* steal the object and destroy the item */
  object = gst_multi_queue_item_steal_object (item);
  gst_multi_queue_item_destroy (item);

  is_buffer = GST_IS_BUFFER (object);

  /* Get running time of the item. Events will have GST_CLOCK_TIME_NONE */
  next_time = get_running_time (&sq->src_segment, object, TRUE);

  GST_LOG_OBJECT (mq, "SingleQueue %d : newid:%d , oldid:%d",
      sq->id, newid, sq->last_oldid);

  /* If we're not-linked, we do some extra work because we might need to
   * wait before pushing. If we're linked but there's a gap in the IDs,
   * or it's the first loop, or we just passed the previous highid,
   * we might need to wake some sleeping pad up, so there's extra work
   * there too */
  GST_MULTI_QUEUE_MUTEX_LOCK (mq);
  if (sq->srcresult == GST_FLOW_NOT_LINKED
      || (sq->last_oldid == G_MAXUINT32) || (newid != (sq->last_oldid + 1))
      || sq->last_oldid > mq->highid) {
    GST_LOG_OBJECT (mq, "CHECKING sq->srcresult: %s",
        gst_flow_get_name (sq->srcresult));

    /* Check again if we're flushing after the lock is taken,
     * the flush flag might have been changed in the meantime */
    if (sq->flushing) {
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      goto out_flushing;
    }

    /* Update the nextid so other threads know when to wake us up */
    sq->nextid = newid;
    sq->next_time = next_time;

    /* Update the oldid (the last ID we output) for highid tracking */
    if (sq->last_oldid != G_MAXUINT32)
      sq->oldid = sq->last_oldid;

    if (sq->srcresult == GST_FLOW_NOT_LINKED) {
      /* Go to sleep until it's time to push this buffer */

      /* Recompute the highid */
      compute_high_id (mq);
      /* Recompute the high time */
      compute_high_time (mq);

      while (((mq->sync_by_running_time && next_time != GST_CLOCK_TIME_NONE &&
                  (mq->high_time == GST_CLOCK_TIME_NONE
                      || next_time >= mq->high_time))
              || (!mq->sync_by_running_time && newid > mq->highid))
          && sq->srcresult == GST_FLOW_NOT_LINKED) {

        GST_DEBUG_OBJECT (mq,
            "queue %d sleeping for not-linked wakeup with "
            "newid %u, highid %u, next_time %" GST_TIME_FORMAT
            ", high_time %" GST_TIME_FORMAT, sq->id, newid, mq->highid,
            GST_TIME_ARGS (next_time), GST_TIME_ARGS (mq->high_time));

        /* Wake up all non-linked pads before we sleep */
        wake_up_next_non_linked (mq);

        mq->numwaiting++;
        g_cond_wait (&sq->turn, &mq->qlock);
        mq->numwaiting--;

        if (sq->flushing) {
          GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
          goto out_flushing;
        }

        /* Recompute the high time */
        compute_high_time (mq);

        GST_DEBUG_OBJECT (mq, "queue %d woken from sleeping for not-linked "
            "wakeup with newid %u, highid %u, next_time %" GST_TIME_FORMAT
            ", high_time %" GST_TIME_FORMAT, sq->id, newid, mq->highid,
            GST_TIME_ARGS (next_time), GST_TIME_ARGS (mq->high_time));
      }

      /* Re-compute the high_id in case someone else pushed */
      compute_high_id (mq);
    } else {
      compute_high_id (mq);
      /* Wake up all non-linked pads */
      wake_up_next_non_linked (mq);
    }
    /* We're done waiting, we can clear the nextid and nexttime */
    sq->nextid = 0;
    sq->next_time = GST_CLOCK_TIME_NONE;
  }
  GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

  if (sq->flushing)
    goto out_flushing;

  GST_LOG_OBJECT (mq, "BEFORE PUSHING sq->srcresult: %s",
      gst_flow_get_name (sq->srcresult));

  /* Update time stats */
  GST_MULTI_QUEUE_MUTEX_LOCK (mq);
  next_time = get_running_time (&sq->src_segment, object, FALSE);
  if (next_time != GST_CLOCK_TIME_NONE) {
    if (sq->last_time == GST_CLOCK_TIME_NONE || sq->last_time < next_time)
      sq->last_time = next_time;
    if (mq->high_time == GST_CLOCK_TIME_NONE || mq->high_time <= next_time) {
      /* Wake up all non-linked pads now that we advanced the high time */
      mq->high_time = next_time;
      wake_up_next_non_linked (mq);
    }
  }
  GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

  /* Try to push out the new object */
  result = gst_single_queue_push_one (mq, sq, object);
  object = NULL;

  /* Check if we pushed something already and if this is
   * now a switch from an active to a non-active stream.
   *
   * If it is, we reset all the waiting streams, let them
   * push another buffer to see if they're now active again.
   * This allows faster switching between streams and prevents
   * deadlocks if downstream does any waiting too.
   */
  GST_MULTI_QUEUE_MUTEX_LOCK (mq);
  if (sq->pushed && sq->srcresult == GST_FLOW_OK
      && result == GST_FLOW_NOT_LINKED) {
    GList *tmp;

    GST_LOG_OBJECT (mq, "SingleQueue %d : Changed from active to non-active",
        sq->id);

    compute_high_id (mq);
    do_update_buffering = TRUE;

    /* maybe no-one is waiting */
    if (mq->numwaiting > 0) {
      /* Else figure out which singlequeue(s) need waking up */
      for (tmp = mq->queues; tmp; tmp = g_list_next (tmp)) {
        GstSingleQueue *sq2 = (GstSingleQueue *) tmp->data;

        if (sq2->srcresult == GST_FLOW_NOT_LINKED) {
          GST_LOG_OBJECT (mq, "Waking up singlequeue %d", sq2->id);
          sq2->pushed = FALSE;
          sq2->srcresult = GST_FLOW_OK;
          g_cond_signal (&sq2->turn);
        }
      }
    }
  }

  if (is_buffer)
    sq->pushed = TRUE;
  sq->srcresult = result;
  sq->last_oldid = newid;

  if (do_update_buffering)
    update_buffering (mq, sq);

  GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

  if (result != GST_FLOW_OK && result != GST_FLOW_NOT_LINKED
      && result != GST_FLOW_EOS)
    goto out_flushing;

  GST_LOG_OBJECT (mq, "AFTER PUSHING sq->srcresult: %s",
      gst_flow_get_name (sq->srcresult));

  return;

out_flushing:
  {
    if (object)
      gst_mini_object_unref (object);

    /* Need to make sure wake up any sleeping pads when we exit */
    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    compute_high_time (mq);
    compute_high_id (mq);
    wake_up_next_non_linked (mq);
    sq->last_query = FALSE;
    g_cond_signal (&sq->query_handled);
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    /* upstream needs to see fatal result ASAP to shut things down,
     * but might be stuck in one of our other full queues;
     * so empty this one and trigger dynamic queue growth. At
     * this point the srcresult is not OK, NOT_LINKED
     * or EOS, i.e. a real failure */
    gst_single_queue_flush_queue (sq, FALSE);
    single_queue_underrun_cb (sq->queue, sq);
    gst_data_queue_set_flushing (sq->queue, TRUE);
    gst_pad_pause_task (sq->srcpad);
    GST_CAT_INFO_OBJECT (multi_queue_debug, mq,
        "SingleQueue[%d] task paused, reason:%s",
        sq->id, gst_flow_get_name (sq->srcresult));
    return;
  }
}

/**
 * gst_multi_queue_chain:
 *
 * This is similar to GstQueue's chain function, except:
 * _ we don't have leak behaviours,
 * _ we push with a unique id (curid)
 */
static GstFlowReturn
gst_multi_queue_chain (GstPad * pad, GstObject * parent, GstBuffer * buffer)
{
  GstSingleQueue *sq;
  GstMultiQueue *mq;
  GstMultiQueueItem *item;
  guint32 curid;
  GstClockTime timestamp, duration;

  sq = gst_pad_get_element_private (pad);
  mq = sq->mqueue;

  /* if eos, we are always full, so avoid hanging incoming indefinitely */
  if (sq->is_eos)
    goto was_eos;

  /* Get a unique incrementing id */
  curid = g_atomic_int_add ((gint *) & mq->counter, 1);

  GST_DEBUG_OBJECT (mq, "SingleQueue %d : about to enqueue buffer %p with id %d",
      sq->id, buffer, curid);

  item = gst_multi_queue_buffer_item_new (GST_MINI_OBJECT_CAST (buffer), curid);
  /** BEGIN: Added for DTS2015102708085 by baihaili(b00311320), 2015/10/26 */
  if (GST_CLOCK_TIME_NONE != GST_BUFFER_DTS(buffer))
    timestamp = GST_BUFFER_DTS(buffer);
  else
    timestamp = GST_BUFFER_TIMESTAMP(buffer);

  sq->last_pts = timestamp;
  /** END:   Added by baihaili(b00311320), 2015/8/29 */
  duration = GST_BUFFER_DURATION (buffer);

  if (!(gst_data_queue_push (sq->queue, (GstDataQueueItem *) item)))
    goto flushing;
  sq->data_cames = TRUE;
  /* update time level, we must do this after pushing the data in the queue so
   * that we never end up filling the queue first. */
  apply_buffer (mq, sq, timestamp, duration, &sq->sink_segment);

done:
  GST_DEBUG_OBJECT (mq, "SingleQueue %d : done, srcresult %s",
      sq->id, gst_flow_get_name(sq->srcresult));
  return sq->srcresult;

  /* ERRORS */
flushing:
  {
    GST_INFO_OBJECT (mq, "SingleQueue %d : exit because task paused, reason: %s",
        sq->id, gst_flow_get_name (sq->srcresult));
    gst_multi_queue_item_destroy (item);
    goto done;
  }
was_eos:
  {
    GST_DEBUG_OBJECT (mq, "we are EOS, dropping buffer, return EOS");
    gst_buffer_unref (buffer);
    return GST_FLOW_EOS;
  }
}

static gboolean
gst_multi_queue_sink_activate_mode (GstPad * pad, GstObject * parent,
    GstPadMode mode, gboolean active)
{
  gboolean res;
  GstSingleQueue *sq;
  GstMultiQueue *mq;

  sq = (GstSingleQueue *) gst_pad_get_element_private (pad);
  mq = (GstMultiQueue *) gst_pad_get_parent (pad);

  /* mq is NULL if the pad is activated/deactivated before being
   * added to the multiqueue */
  if (mq)
    GST_MULTI_QUEUE_MUTEX_LOCK (mq);

  switch (mode) {
    case GST_PAD_MODE_PUSH:
      if (active) {
        /* All pads start off linked until they push one buffer */
        sq->srcresult = GST_FLOW_OK;
        sq->pushed = FALSE;
        gst_data_queue_set_flushing (sq->queue, FALSE);
      } else {
        sq->srcresult = GST_FLOW_FLUSHING;
        sq->last_query = FALSE;
        g_cond_signal (&sq->query_handled);
        gst_data_queue_set_flushing (sq->queue, TRUE);

        /* Wait until streaming thread has finished */
        if (mq)
          GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
        GST_PAD_STREAM_LOCK (pad);
        if (mq)
          GST_MULTI_QUEUE_MUTEX_LOCK (mq);
        gst_data_queue_flush (sq->queue);
        if (mq)
          GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
        GST_PAD_STREAM_UNLOCK (pad);
        if (mq)
          GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      }
      res = TRUE;
      break;
    default:
      res = FALSE;
      break;
  }

  if (mq) {
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
    gst_object_unref (mq);
  }

  return res;
}

static gboolean
gst_multi_queue_sink_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  GstSingleQueue *sq;
  GstMultiQueue *mq;
  guint32 curid;
  GstMultiQueueItem *item;
  gboolean res;
  GstEventType type;
  GstEvent *sref = NULL;

  sq = (GstSingleQueue *) gst_pad_get_element_private (pad);
  mq = (GstMultiQueue *) parent;

  type = GST_EVENT_TYPE (event);

  switch (type) {
    case GST_EVENT_FLUSH_START:
      GST_DEBUG_OBJECT (mq, "SingleQueue %d : received flush start event",
          sq->id);

      res = gst_pad_push_event (sq->srcpad, event);

      /* wake up threads waiting on cond */
      GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      GST_MULTI_QUEUE_BROADCAST(mq);
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

      gst_single_queue_flush (mq, sq, TRUE, FALSE);
      /* BEGIN: Added for DTS2015102500281 by liurongliang(l00180035), 2015/10/27 */
      mq->last_percent = 0;
      mq->percent = 0;
      /* END: Added for DTS2015102500281 by liurongliang(l00180035), 2015/10/27 */

      goto done;

    case GST_EVENT_FLUSH_STOP:
      GST_DEBUG_OBJECT (mq, "SingleQueue %d : received flush stop event",
          sq->id);

      res = gst_pad_push_event (sq->srcpad, event);

      gst_single_queue_flush (mq, sq, FALSE, FALSE);
      goto done;
    case GST_EVENT_SEGMENT:
      /* take ref because the queue will take ownership and we need the event
       * afterwards to update the segment */
      sref = gst_event_ref (event);
      GST_DEBUG_OBJECT (mq, "SingleQueue %d : received segment event",
          sq->id);
      break;

    case GST_EVENT_GAP:
      /* wake up tasks of inactive pad */
      if (pad == mq->active_audio_pad) {
        GST_MULTI_QUEUE_MUTEX_LOCK (mq);
        GST_MULTI_QUEUE_BROADCAST(mq);
        GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      }
      break;

    default:
      if (!(GST_EVENT_IS_SERIALIZED (event))) {
        res = gst_pad_push_event (sq->srcpad, event);
        goto done;
      }
      break;
  }

  /* if eos, we are always full, so avoid hanging incoming indefinitely */
  if (sq->is_eos)
    goto was_eos;

  /* Get an unique incrementing id. */
  curid = g_atomic_int_add ((gint *) & mq->counter, 1);

  item = gst_multi_queue_mo_item_new ((GstMiniObject *) event, curid);

  GST_DEBUG_OBJECT (mq,
      "SingleQueue %d : Enqueuing event %p of type %s with id %d",
      sq->id, event, GST_EVENT_TYPE_NAME (event), curid);

  if (!(res = gst_data_queue_push (sq->queue, (GstDataQueueItem *) item)))
    goto flushing;

  /* mark EOS when we received one, we must do that after putting the
   * buffer in the queue because EOS marks the buffer as filled. No need to take
   * a lock, the _check_full happens from this thread only, right before pushing
   * into dataqueue. */
  switch (type) {
    case GST_EVENT_EOS:
      sq->is_eos = TRUE;
      /* EOS affects the buffering state */
      update_buffering (mq, sq);
      single_queue_overrun_cb (sq->queue, sq);
      break;
    case GST_EVENT_SEGMENT:
      apply_segment (mq, sq, sref, &sq->sink_segment);
      gst_event_unref (sref);
      break;
    default:
      break;
  }
done:
  return res;

flushing:
  {
    GST_LOG_OBJECT (mq, "SingleQueue %d : exit because task paused, reason: %s",
        sq->id, gst_flow_get_name (sq->srcresult));
    if (sref)
      gst_event_unref (sref);
    gst_multi_queue_item_destroy (item);
    goto done;
  }
was_eos:
  {
    GST_DEBUG_OBJECT (mq, "we are EOS, dropping event, return FALSE");
    gst_event_unref (event);
    res = FALSE;
    goto done;
  }
}

static gboolean
gst_multi_queue_sink_query (GstPad * pad, GstObject * parent, GstQuery * query)
{
  gboolean res;
  GstSingleQueue *sq;
  GstMultiQueue *mq;

  sq = (GstSingleQueue *) gst_pad_get_element_private (pad);
  mq = (GstMultiQueue *) parent;

  switch (GST_QUERY_TYPE (query)) {
    default:
      if (GST_QUERY_IS_SERIALIZED (query)) {
        guint32 curid;
        GstMultiQueueItem *item;

        GST_MULTI_QUEUE_MUTEX_LOCK (mq);
        if (sq->srcresult != GST_FLOW_OK)
          goto out_flushing;

        /* serialized events go in the queue. We need to be certain that we
         * don't cause deadlocks waiting for the query return value. We check if
         * the queue is empty (nothing is blocking downstream and the query can
         * be pushed for sure) or we are not buffering. If we are buffering,
         * the pipeline waits to unblock downstream until our queue fills up
         * completely, which can not happen if we block on the query..
         * Therefore we only potentially block when we are not buffering. */
        if (!mq->use_buffering || gst_data_queue_is_empty (sq->queue)) {
          /* Get an unique incrementing id. */
          curid = g_atomic_int_add ((gint *) & mq->counter, 1);

          item = gst_multi_queue_mo_item_new ((GstMiniObject *) query, curid);

          GST_DEBUG_OBJECT (mq,
              "SingleQueue %d : Enqueuing query %p of type %s with id %d",
              sq->id, query, GST_QUERY_TYPE_NAME (query), curid);
          res = gst_data_queue_push (sq->queue, (GstDataQueueItem *) item);
          g_cond_wait (&sq->query_handled, &mq->qlock);
          res = sq->last_query;
        } else {
          GST_DEBUG_OBJECT (mq, "refusing query, we are buffering and the "
              "queue is not empty");
          res = FALSE;
        }
        GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      } else {
        /* default handling */
        res = gst_pad_query_default (pad, parent, query);
      }
      break;
  }
  return res;

out_flushing:
  {
    GST_DEBUG_OBJECT (mq, "Flushing");
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
    return FALSE;
  }
}

static gboolean
gst_multi_queue_src_activate_mode (GstPad * pad, GstObject * parent,
    GstPadMode mode, gboolean active)
{
  GstMultiQueue *mq;
  GstSingleQueue *sq;
  gboolean result;

  sq = (GstSingleQueue *) gst_pad_get_element_private (pad);
  mq = sq->mqueue;

  GST_DEBUG_OBJECT (mq, "SingleQueue %d", sq->id);

  switch (mode) {
    case GST_PAD_MODE_PUSH:
      if (active) {
        result = gst_single_queue_flush (mq, sq, FALSE, TRUE);
      } else {
        result = gst_single_queue_flush (mq, sq, TRUE, TRUE);
        /* make sure streaming finishes */
        result |= gst_pad_stop_task (pad);
      }
      break;
    default:
      result = FALSE;
      break;
  }
  return result;
}

static gboolean
gst_multi_queue_src_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  GstSingleQueue *sq = gst_pad_get_element_private (pad);
  GstMultiQueue *mq = sq->mqueue;
  gboolean ret;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_RECONFIGURE:
      GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      if (sq->srcresult == GST_FLOW_NOT_LINKED) {
        sq->srcresult = GST_FLOW_OK;
        g_cond_signal (&sq->turn);
      }
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

      ret = gst_pad_push_event (sq->sinkpad, event);
      break;
    default:
      ret = gst_pad_push_event (sq->sinkpad, event);
      break;
  }

  return ret;
}

static gboolean
gst_multi_queue_src_query (GstPad * pad, GstObject * parent, GstQuery * query)
{
  gboolean res;

  /* FIXME, Handle position offset depending on queue size */
  switch (GST_QUERY_TYPE (query)) {
    default:
      /* default handling */
      res = gst_pad_query_default (pad, parent, query);
      break;
  }
  return res;
}

/*
 * Next-non-linked functions
 */

/* WITH LOCK TAKEN */
static void
wake_up_next_non_linked (GstMultiQueue * mq)
{
  GList *tmp;

  /* maybe no-one is waiting */
  if (mq->numwaiting < 1)
    return;

  /* Else figure out which singlequeue(s) need waking up */
  for (tmp = mq->queues; tmp; tmp = g_list_next (tmp)) {
    GstSingleQueue *sq = (GstSingleQueue *) tmp->data;

    if (sq->srcresult == GST_FLOW_NOT_LINKED) {
      if ((mq->sync_by_running_time && mq->high_time != GST_CLOCK_TIME_NONE
              && sq->next_time != GST_CLOCK_TIME_NONE
              && sq->next_time >= mq->high_time)
          || (sq->nextid != 0 && sq->nextid <= mq->highid)) {
        GST_LOG_OBJECT (mq, "Waking up singlequeue %d", sq->id);
        g_cond_signal (&sq->turn);
      }
    }
  }
}

/* WITH LOCK TAKEN */
static void
compute_high_id (GstMultiQueue * mq)
{
  /* The high-id is either the highest id among the linked pads, or if all
   * pads are not-linked, it's the lowest not-linked pad */
  GList *tmp;
  guint32 lowest = G_MAXUINT32;
  guint32 highid = G_MAXUINT32;

  for (tmp = mq->queues; tmp; tmp = g_list_next (tmp)) {
    GstSingleQueue *sq = (GstSingleQueue *) tmp->data;

    GST_LOG_OBJECT (mq, "inspecting sq:%d , nextid:%d, oldid:%d, srcresult:%s",
        sq->id, sq->nextid, sq->oldid, gst_flow_get_name (sq->srcresult));

    if (sq->srcresult == GST_FLOW_NOT_LINKED) {
      /* No need to consider queues which are not waiting */
      if (sq->nextid == 0) {
        GST_LOG_OBJECT (mq, "sq:%d is not waiting - ignoring", sq->id);
        continue;
      }

      if (sq->nextid < lowest)
        lowest = sq->nextid;
    } else if (sq->srcresult != GST_FLOW_EOS) {
      /* If we don't have a global highid, or the global highid is lower than
       * this single queue's last outputted id, store the queue's one,
       * unless the singlequeue is at EOS (srcresult = EOS) */
      if ((highid == G_MAXUINT32) || (sq->oldid > highid))
        highid = sq->oldid;
    }
  }

  if (highid == G_MAXUINT32 || lowest < highid)
    mq->highid = lowest;
  else
    mq->highid = highid;

  GST_LOG_OBJECT (mq, "Highid is now : %u, lowest non-linked %u", mq->highid,
      lowest);
}

/* WITH LOCK TAKEN */
static void
compute_high_time (GstMultiQueue * mq)
{
  /* The high-id is either the highest id among the linked pads, or if all
   * pads are not-linked, it's the lowest not-linked pad */
  GList *tmp;
  GstClockTime highest = GST_CLOCK_TIME_NONE;
  GstClockTime lowest = GST_CLOCK_TIME_NONE;

  for (tmp = mq->queues; tmp; tmp = g_list_next (tmp)) {
    GstSingleQueue *sq = (GstSingleQueue *) tmp->data;

    GST_LOG_OBJECT (mq,
        "inspecting sq:%d , next_time:%" GST_TIME_FORMAT ", last_time:%"
        GST_TIME_FORMAT ", srcresult:%s", sq->id, GST_TIME_ARGS (sq->next_time),
        GST_TIME_ARGS (sq->last_time), gst_flow_get_name (sq->srcresult));

    if (sq->srcresult == GST_FLOW_NOT_LINKED) {
      /* No need to consider queues which are not waiting */
      if (sq->next_time == GST_CLOCK_TIME_NONE) {
        GST_LOG_OBJECT (mq, "sq:%d is not waiting - ignoring", sq->id);
        continue;
      }

      if (lowest == GST_CLOCK_TIME_NONE || sq->next_time < lowest)
        lowest = sq->next_time;
    } else if (sq->srcresult != GST_FLOW_EOS) {
      /* If we don't have a global highid, or the global highid is lower than
       * this single queue's last outputted id, store the queue's one,
       * unless the singlequeue is at EOS (srcresult = EOS) */
      if (highest == GST_CLOCK_TIME_NONE || sq->last_time > highest)
        highest = sq->last_time;
    }
  }

  mq->high_time = highest;

  GST_LOG_OBJECT (mq,
      "High time is now : %" GST_TIME_FORMAT ", lowest non-linked %"
      GST_TIME_FORMAT, GST_TIME_ARGS (mq->high_time), GST_TIME_ARGS (lowest));
}

/** BEGIN: Added for DTS2015082102992 by baihaili(b00311320), 2015/8/29 */
static gint get_lowest_percent (GstMultiQueue * mq)
{
  GList *tmp;
  gint lowest_percent = 100;

  for (tmp = mq->queues; tmp; tmp = g_list_next (tmp)) {
    GstSingleQueue *sq = (GstSingleQueue *) tmp->data;

    GST_DEBUG_OBJECT (mq,"inspecting sq:%d ,percent:%d,srcresult:%d"
                     ,sq->id,sq->percent,sq->srcresult);

    if (sq->srcresult == GST_FLOW_NOT_LINKED
        || sq->srcresult == GST_FLOW_EOS) {
      continue;
    }

    /** if any one of the single queues' is full,then we would
     * report it, or else maybe it will block other single queues*/
    if (gst_data_queue_is_full(sq->queue))
    {
        lowest_percent = 100;
        break;
    }
    if (sq->percent < lowest_percent){
        lowest_percent = sq->percent;
    }
  }

  GST_DEBUG_OBJECT (mq,"Lowest percent is :%d", lowest_percent);
  return lowest_percent;
}
/** END:   Added by baihaili(b00311320), 2015/8/29 */

#define IS_FILLED(q, format, value) (((q)->max_size.format) != 0 && \
     ((q)->max_size.format) <= (value))

static void push_eos_downstream(GstSingleQueue * sq)
{
  gboolean err ;
  GstEvent* ev_eos = gst_event_new_eos();

  if(ev_eos){
    GST_WARNING("mq self push eos downstream begin...");
    err = gst_pad_push_event(sq->srcpad, ev_eos);
    GST_WARNING("push eos return err=%d", err);
  }else{
    GST_WARNING("ev_eos is null");
  }

  return;
}

/*
 * GstSingleQueue functions
 */
static void
single_queue_overrun_cb (GstDataQueue * dq, GstSingleQueue * sq)
{
  GstMultiQueue *mq = sq->mqueue;
  GList *tmp;
  GstDataQueueSize size;
  gboolean filled = TRUE;

  gst_data_queue_get_level (sq->queue, &size);

  GST_LOG_OBJECT (mq,
      "Single Queue %d: EOS %d, visible %u/%u, bytes %u/%u, time %"
      G_GUINT64_FORMAT "/%" G_GUINT64_FORMAT, sq->id, sq->is_eos, size.visible,
      sq->max_size.visible, size.bytes, sq->max_size.bytes, sq->cur_time,
      sq->max_size.time);

  GST_MULTI_QUEUE_MUTEX_LOCK (mq);

  /* check if we reached the hard time/bytes limits */
  if (sq->is_eos || IS_FILLED (sq, bytes, size.bytes) ||
      IS_FILLED (sq, time, sq->cur_time)) {
    goto done;
  }

  /* if hard limits are not reached then we allow one more buffer in the full
   * queue, but only if any of the other singelqueues are empty */
  for (tmp = mq->queues; tmp; tmp = g_list_next (tmp)) {
    GstSingleQueue *oq = (GstSingleQueue *) tmp->data;
    GST_DEBUG_OBJECT (mq, "Checking Queue %d,sq:%d", oq->id, sq->id);

    if (oq == sq)
      continue;

    if (oq->srcresult == GST_FLOW_NOT_LINKED) {
      GST_DEBUG_OBJECT (mq, "Queue %d is not-linked", oq->id);
      continue;
    }

    if (gst_data_queue_is_empty (oq->queue)) {
      GST_LOG_OBJECT (mq, "Queue %d is empty", oq->id);
      if (IS_FILLED (sq, visible, size.visible)) {
        sq->max_size.visible = size.visible + 1;
        GST_DEBUG_OBJECT (mq,
            "Queue %d is empty, bumping single queue %d max visible to %d",
            oq->id, sq->id, sq->max_size.visible);
        filled = FALSE;
        break;
      }
    }
  }

done:
  for (tmp = mq->queues; mq->is_after_demux && tmp; tmp = g_list_next (tmp)) {
    GstSingleQueue *oq = (GstSingleQueue *) tmp->data;
    GST_DEBUG_OBJECT (mq, "Checking Queue %d,sq:%d", oq->id, sq->id);

    if (oq == sq)
      continue;

    if (oq->srcresult == GST_FLOW_NOT_LINKED) {
      GST_INFO_OBJECT (mq, "Queue %d is not-linked", oq->id);
      continue;
    }

    if (!oq->data_cames && !oq->is_eos) {
      if (mq->use_max_time_check_buffer_full) {
        /*
         * For DTS2016042802273:
         *   The stream in this DTS begins with 13s audio frames, between this 13s audio frames,
         *   there is no video frame; after this 13s audio frames, video and audio frames interwoven good.
         * To solve this problem:
         *   If queue.buffer.time is full but queue.buffer.size is very small, queue.buffer is not handled as full.
         */
        GST_WARNING_OBJECT (mq,
            "Queue %d no data comes but other q is full(over max_time), not use max_time now", oq->id);
        mq->use_max_time_check_buffer_full = FALSE;
      } else {
        GST_INFO_OBJECT (mq,
            "Queue %d no data comes but other q is full(over max_size), push eos to downstream", oq->id);
        //if one queue is full, buffer other queue is not come, we push eos to downstream.
        oq->is_eos = TRUE;
        GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
        push_eos_downstream(oq);
        GST_MULTI_QUEUE_MUTEX_LOCK (mq);
      }
    }
  }

  GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

  /* Overrun is always forwarded, since this is blocking the upstream element */
  if (filled) {
    GST_DEBUG_OBJECT (mq, "Queue %d is filled, signalling overrun", sq->id);
    sq->status = GST_SME_OVERRUN;
    g_signal_emit (mq, gst_multi_queue_signals[SIGNAL_OVERRUN], 0);
  }
}

static void
single_queue_underrun_cb (GstDataQueue * dq, GstSingleQueue * sq)
{
  gboolean empty = TRUE;
  GstMultiQueue *mq = sq->mqueue;
  GList *tmp;

  if (sq->srcresult == GST_FLOW_NOT_LINKED) {
    GST_LOG_OBJECT (mq, "Single Queue %d is empty but not-linked", sq->id);
    return;
  } else {
    GST_LOG_OBJECT (mq,
        "Single Queue %d is empty, Checking other single queues", sq->id);
  }

  GST_MULTI_QUEUE_MUTEX_LOCK (mq);
  for (tmp = mq->queues; tmp; tmp = g_list_next (tmp)) {
    GstSingleQueue *oq = (GstSingleQueue *) tmp->data;

    if (gst_data_queue_is_full (oq->queue)) {
      GstDataQueueSize size;

      gst_data_queue_get_level (oq->queue, &size);
      if (IS_FILLED (oq, visible, size.visible)) {
        oq->max_size.visible = size.visible + 1;
        GST_DEBUG_OBJECT (mq,
            "queue %d is filled, bumping its max visible to %d", oq->id,
            oq->max_size.visible);
        gst_data_queue_limits_changed (oq->queue);
      }
    }
    if (!gst_data_queue_is_empty (oq->queue))
      empty = FALSE;
  }
  GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

  if (empty) {
    GST_DEBUG_OBJECT (mq, "All queues are empty, signalling it");
    sq->status = GST_SME_UNDERRUN;
    g_signal_emit (mq, gst_multi_queue_signals[SIGNAL_UNDERRUN], 0);
  }
}

static gboolean
single_queue_check_full (GstDataQueue * dataq, guint visible, guint bytes,
    guint64 time, GstSingleQueue * sq)
{
  gboolean res;
  GstMultiQueue *mq = sq->mqueue;
  gfloat buffer_bytes_level = 0;
  gfloat buffer_time_level = 0;
  gfloat buffer_level = 0;

  GST_DEBUG_OBJECT (mq,
      "queue %d: visible %u/%u, bytes %u/%u, time %" G_GUINT64_FORMAT "/%"
      G_GUINT64_FORMAT, sq->id, visible, sq->max_size.visible, bytes,
      sq->max_size.bytes, sq->cur_time, sq->max_size.time);

  /* we are always filled on EOS */
  if (sq->is_eos) {
      return TRUE;
  }

  /* multiqueue status managing, added by xueping. */
  if ((GST_SME_OVERRUN==sq->status)||(GST_SME_UNDERRUN==sq->status))
  {
      buffer_bytes_level = (gfloat)bytes / sq->max_size.bytes;
      if ((mq->use_buffering )&&(GST_CLOCK_TIME_IS_VALID(sq->cur_time)))
      {
          buffer_time_level = sq->cur_time*1.0 / sq->max_size.time;
      }
      buffer_level = MAX(buffer_bytes_level, buffer_time_level);
      if ((buffer_level >= GST_SME_DATA_Q_LOW_LVL )&&(buffer_level <= GST_SME_DATA_Q_HIGH_LVL))
      {
          sq->status = GST_SME_NORMAL;
          g_signal_emit(mq, gst_multi_queue_signals[SIGNAL_NORMALISING], 0);
      }
      GST_DEBUG_OBJECT (mq, "@gstmultiqueue@ queue[%d], bytes_level: %f, time_level: %f, buffer_level: %f",
          sq->id, buffer_bytes_level, buffer_time_level, buffer_level);
  }

#ifdef __SME_MQ_CTRL__

  //GST_INFO_OBJECT (mq, "bytes=%lu, cur_time=%llu", bytes, sq->cur_time);

  /*
   * For DTS2016042802273:
   *   The stream in this DTS begins with 13s audio frames, between this 13s audio frames,
   *   there is no video frame; after this 13s audio frames, video and audio frames interwoven good.
   * To solve this problem:
   *   If queue.buffer.time is full but queue.buffer.size is very small, queue.buffer is not handled as full.
   */
  if (mq->use_max_time_check_buffer_full && (GST_CLOCK_TIME_IS_VALID(sq->cur_time)) )
    res = IS_FILLED (sq, bytes, bytes) || IS_FILLED (sq, time, sq->cur_time);
  else
    res = IS_FILLED (sq, bytes, bytes);

  if (res)
    GST_WARNING_OBJECT (mq,
      "queue %d: visible %u/%u, bytes %u/%u, time %" G_GUINT64_FORMAT "/%"
      G_GUINT64_FORMAT ", res=%d", sq->id, visible, sq->max_size.visible, bytes,
      sq->max_size.bytes, sq->cur_time, sq->max_size.time, res);

  return res;
#else
  /* we never go past the max visible items unless we are in buffering mode */
  if (!mq->use_buffering && IS_FILLED (sq, visible, visible))
    return TRUE;

  /* check time or bytes */
  res = IS_FILLED (sq, time, sq->cur_time) || IS_FILLED (sq, bytes, bytes);
#endif
  return res;
}

static void
gst_single_queue_flush_queue (GstSingleQueue * sq, gboolean full)
{
  GstDataQueueItem *sitem;
  GstMultiQueueItem *mitem;
  gboolean was_flushing = FALSE;

  while (!gst_data_queue_is_empty (sq->queue)) {
    GstMiniObject *data;

    /* FIXME: If this fails here although the queue is not empty,
     * we're flushing... but we want to rescue all sticky
     * events nonetheless.
     */
    if (!gst_data_queue_pop (sq->queue, &sitem)) {
      was_flushing = TRUE;
      gst_data_queue_set_flushing (sq->queue, FALSE);
      continue;
    }

    mitem = (GstMultiQueueItem *) sitem;

    data = sitem->object;

    if (!full && !mitem->is_query && GST_IS_EVENT (data)
        && GST_EVENT_IS_STICKY (data)
        && GST_EVENT_TYPE (data) != GST_EVENT_SEGMENT
        && GST_EVENT_TYPE (data) != GST_EVENT_EOS) {
      gst_pad_store_sticky_event (sq->srcpad, GST_EVENT_CAST (data));
    }

    sitem->destroy (sitem);
  }

  gst_data_queue_flush (sq->queue);
  if (was_flushing)
    gst_data_queue_set_flushing (sq->queue, TRUE);
}

static void
gst_single_queue_free (GstSingleQueue * sq)
{
  /* DRAIN QUEUE */
  gst_data_queue_flush (sq->queue);
  g_object_unref (sq->queue);
  g_cond_clear (&sq->turn);
  g_cond_clear (&sq->query_handled);
  g_free (sq);
}

static GstSmeSingleQueueType
gst_single_queue_get_type(GstSingleQueue *sq)
{
  GstCaps* sinkpad_caps = gst_pad_get_current_caps(sq->sinkpad);
  gchar* str_caps = gst_caps_to_string(sinkpad_caps);
  GstSmeSingleQueueType sq_type = SQ_T_UNKOWN;

  if ( strstr(str_caps, "video") ) {
    sq_type = SQ_T_VIDEO;
  }
  else if(strstr(str_caps, "audio")) {
    sq_type = SQ_T_AUDIO;
  }
  else if(strstr(str_caps, "text")) {
    sq_type = SQ_T_TEXT;
  }
  else {
    GST_INFO("Unknow single queue type.");

    g_free(str_caps);
    if ( sinkpad_caps ) {
      gst_caps_unref(sinkpad_caps);
      sinkpad_caps = NULL;
    }

    return sq_type;
  }

  if ( sinkpad_caps ) {
    gst_caps_unref(sinkpad_caps);
    sinkpad_caps = NULL;
  }

  if (str_caps) {
    g_free(str_caps);
    str_caps = NULL;
  }

  return sq_type;
}

static GstSingleQueue *
gst_single_queue_new (GstMultiQueue * mqueue, guint id)
{
  GstSingleQueue *sq;
  gchar *name;
  GList *tmp;
  guint temp_id = (id == -1) ? 0 : id;

  GST_MULTI_QUEUE_MUTEX_LOCK (mqueue);

  /* Find an unused queue ID, if possible the passed one */
  for (tmp = mqueue->queues; tmp; tmp = g_list_next (tmp)) {
    GstSingleQueue *sq2 = (GstSingleQueue *) tmp->data;
    /* This works because the IDs are sorted in ascending order */
    if (sq2->id == temp_id) {
      /* If this ID was requested by the caller return NULL,
       * otherwise just get us the next one */
      if (id == -1)
        temp_id = sq2->id + 1;
      else
        return NULL;
    } else if (sq2->id > temp_id) {
      break;
    }
  }

  sq = g_new0 (GstSingleQueue, 1);
  mqueue->nbqueues++;
  sq->id = temp_id;

  mqueue->queues = g_list_insert_before (mqueue->queues, tmp, sq);
  mqueue->queues_cookie++;

  /* copy over max_size and extra_size so we don't need to take the lock
   * any longer when checking if the queue is full. */
  sq->max_size.visible = mqueue->max_size.visible;
  sq->max_size.bytes = mqueue->max_size.bytes;
  sq->max_size.time = mqueue->max_size.time;

  sq->extra_size.visible = mqueue->extra_size.visible;
  sq->extra_size.bytes = mqueue->extra_size.bytes;
  sq->extra_size.time = mqueue->extra_size.time;

  GST_DEBUG_OBJECT (mqueue, "Creating GstSingleQueue id:%d", sq->id);

  sq->mqueue = mqueue;
  sq->srcresult = GST_FLOW_FLUSHING;
  sq->pushed = FALSE;
  sq->queue = gst_data_queue_new ((GstDataQueueCheckFullFunction)
      single_queue_check_full,
      (GstDataQueueFullCallback) single_queue_overrun_cb,
      (GstDataQueueEmptyCallback) single_queue_underrun_cb, sq);
  sq->is_eos = FALSE;
  sq->flushing = FALSE;
  /** BEGIN: Added for DTS2015082102992 by baihaili(b00311320), 2015/8/29 */
  sq->percent = 0;
  /** END:   Added by baihaili(b00311320), 2015/8/29 */
  gst_segment_init (&sq->sink_segment, GST_FORMAT_TIME);
  gst_segment_init (&sq->src_segment, GST_FORMAT_TIME);

  sq->nextid = 0;
  sq->oldid = 0;
  sq->next_time = GST_CLOCK_TIME_NONE;
  sq->last_time = GST_CLOCK_TIME_NONE;
  g_cond_init (&sq->turn);
  g_cond_init (&sq->query_handled);

  sq->sinktime = GST_CLOCK_TIME_NONE;
  sq->srctime = GST_CLOCK_TIME_NONE;
  sq->sink_tainted = TRUE;
  sq->src_tainted = TRUE;
  sq->is_active = TRUE;
  sq->active_transiting = FALSE;
  sq->active_flushing = FALSE;

  sq->last_post_time = GST_CLOCK_TIME_NONE;
  sq->last_pts = GST_CLOCK_TIME_NONE;
  /** BEGIN: Added for DTS2015102709689 by baihaili(b00311320), 2015/10/27 */
  sq->last_post_avinfo_time = GST_CLOCK_TIME_NONE;
  /* END:   Added for DTS2015102709689 by baihaili(b00311320), 2015/10/27 */
  name = g_strdup_printf ("sink_%u", sq->id);
  sq->sinkpad = gst_pad_new_from_static_template (&sinktemplate, name);
  g_free (name);

  gst_pad_set_chain_function (sq->sinkpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_chain));
  gst_pad_set_activatemode_function (sq->sinkpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_sink_activate_mode));
  gst_pad_set_event_function (sq->sinkpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_sink_event));
  gst_pad_set_query_function (sq->sinkpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_sink_query));
  gst_pad_set_iterate_internal_links_function (sq->sinkpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_iterate_internal_links));
  GST_OBJECT_FLAG_SET (sq->sinkpad, GST_PAD_FLAG_PROXY_CAPS);

  name = g_strdup_printf ("src_%u", sq->id);
  sq->srcpad = gst_pad_new_from_static_template (&srctemplate, name);
  g_free (name);

  gst_pad_set_activatemode_function (sq->srcpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_src_activate_mode));
  gst_pad_set_event_function (sq->srcpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_src_event));
  gst_pad_set_query_function (sq->srcpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_src_query));
  gst_pad_set_iterate_internal_links_function (sq->srcpad,
      GST_DEBUG_FUNCPTR (gst_multi_queue_iterate_internal_links));
  GST_OBJECT_FLAG_SET (sq->srcpad, GST_PAD_FLAG_PROXY_CAPS);

  gst_pad_set_element_private (sq->sinkpad, (gpointer) sq);
  gst_pad_set_element_private (sq->srcpad, (gpointer) sq);

  sq->sq_type = gst_single_queue_get_type(sq);

  GST_MULTI_QUEUE_MUTEX_UNLOCK (mqueue);

  /* only activate the pads when we are not in the NULL state
   * and add the pad under the state_lock to prevend state changes
   * between activating and adding */
  g_rec_mutex_lock (GST_STATE_GET_LOCK (mqueue));
  if (GST_STATE_TARGET (mqueue) != GST_STATE_NULL) {
    gst_pad_set_active (sq->srcpad, TRUE);
    gst_pad_set_active (sq->sinkpad, TRUE);
  }
  gst_element_add_pad (GST_ELEMENT (mqueue), sq->srcpad);
  gst_element_add_pad (GST_ELEMENT (mqueue), sq->sinkpad);
  g_rec_mutex_unlock (GST_STATE_GET_LOCK (mqueue));

  GST_DEBUG_OBJECT (mqueue, "GstSingleQueue [%d] created and pads added",
      sq->id);

  return sq;
}

static void
post_all_buffers_message(GstMultiQueue * mq, GstSingleQueue * sq)
{
  GstStructure *s;
  GstDataQueueSize size;
  GstMessage *m;
  GstCaps* sinkpad_caps = gst_pad_get_current_caps(sq->sinkpad);
  gchar* str_caps = gst_caps_to_string(sinkpad_caps);
  gchar* data_type;

  if (strstr(str_caps, "video")) {
    data_type = "video";
  }
  else if(strstr(str_caps, "audio")) {
    data_type = "audio";
  }
  else {
    GST_INFO_OBJECT (mq, "caps :%s",str_caps);
    gst_caps_unref(sinkpad_caps);
    g_free(str_caps);
    return;
  }
  gst_data_queue_get_level (sq->queue, &size);
  GST_DEBUG_OBJECT (mq, "post %s buffer message",data_type);

  GST_DEBUG_OBJECT (mq,
      "queue %d: visible %u/%u, bytes %u/%u, time %" G_GUINT64_FORMAT "/%"
      G_GUINT64_FORMAT, sq->id, size.visible, sq->max_size.visible,
      size.bytes, sq->max_size.bytes, sq->cur_time, sq->max_size.time);

  s = gst_structure_new ("multiqueue-buffer-statistics",
               "queue-type", G_TYPE_STRING, data_type,
               "buffer-size", G_TYPE_UINT, size.bytes,
               "buffer-play-time", G_TYPE_UINT64, sq->cur_time,
               "buffer-last-pts", G_TYPE_UINT64, sq->last_pts,
                NULL);
   m = gst_message_new_element (GST_OBJECT_CAST (mq),s);
   gst_element_post_message (GST_ELEMENT_CAST (mq),m);
   gst_caps_unref(sinkpad_caps);
   g_free(str_caps);
}

static gboolean select_audio_track (GstMultiQueue * mq, GstPad *pad)
{
  GList *tmp;
  GstSingleQueue *sq, *active_sq;
  GstPad *sinkpad, *active_sinkpad;
  GstCaps* sinkpad_caps;
  gchar *str_caps;
  gboolean is_audio = FALSE, ret = FALSE;

  active_sq = gst_pad_get_element_private (pad);
  sinkpad_caps = gst_pad_get_current_caps(active_sq->sinkpad);
  str_caps = gst_caps_to_string(sinkpad_caps);

  GST_INFO_OBJECT (mq, "select audio pad %s, caps %s",
      GST_PAD_NAME(pad), str_caps);

  if(!strstr(str_caps, "audio")) {
    gst_caps_unref(sinkpad_caps);
    g_free(str_caps);
    GST_ERROR_OBJECT(mq, "it's not an audio pad, don't support");
    return FALSE;
  }

  gst_caps_unref(sinkpad_caps);
  g_free(str_caps);

  /* deactivate all audio tracks excepts the one which leaves as active */
  for (tmp = mq->queues; tmp; tmp = g_list_next (tmp)) {
    sq = (GstSingleQueue *) tmp->data;

    sinkpad = sq->sinkpad;

    sinkpad_caps = gst_pad_get_current_caps(sq->sinkpad);
    str_caps = gst_caps_to_string(sinkpad_caps);

    if(strstr(str_caps, "audio")) {
      is_audio = TRUE;
    } else {
      is_audio = FALSE;
    }

    gst_caps_unref(sinkpad_caps);

    if (!is_audio || !sq->is_active || sq == active_sq) {
      g_free(str_caps);
      continue;
    }

    GST_INFO_OBJECT (mq, "deactivate audio pad %s, caps %s",
        GST_PAD_NAME(sinkpad), str_caps);

    g_free(str_caps);
    /* deactivate the audio track
     * push eos event to downstream elements
     */
    ret = activate_audio_track(mq, sq, FALSE);
  }

  /* active the pad */
  if (!active_sq->is_active) {
    GST_INFO_OBJECT (mq, "activate audio");
    ret = activate_audio_track(mq, active_sq, TRUE);
  }

  /* initialize active audio pad if needed */
  GST_MULTI_QUEUE_MUTEX_LOCK(mq);
  if (mq->active_audio_pad == NULL) {
    mq->active_audio_pad = sq->sinkpad;
  }
  GST_MULTI_QUEUE_MUTEX_UNLOCK(mq);

  return ret;
}

static gboolean
activate_audio_track(GstMultiQueue *mq, GstSingleQueue *sq, gboolean active)
{
  GstEvent *flush_start_event, *flush_stop_event;
  gboolean ret = TRUE;

  GST_INFO_OBJECT (mq, "%s audio pad %s",
      active ? "active" : "deactive", GST_PAD_NAME(sq->srcpad));

  GST_MULTI_QUEUE_MUTEX_LOCK(mq);
  sq->active_transiting = TRUE;

  if (active && !sq->is_active) {
    sq->is_active = TRUE;
    mq->active_audio_pad = sq->sinkpad;
  } else if (!active && sq->is_active) {
    sq->is_active = FALSE;
  }

  GST_MULTI_QUEUE_BROADCAST(mq);

  GST_MULTI_QUEUE_MUTEX_UNLOCK(mq);

  return ret;
}

static gboolean flush_transiting_audio_track(GstMultiQueue *mq,
    GstSingleQueue *sq)
{
  GstEvent *flush_start_event, *flush_stop_event, *segment_event;
  GstSegment segment;
  gboolean ret = TRUE;

  GST_MULTI_QUEUE_MUTEX_LOCK(mq);
  if (!sq->active_transiting) {
    GST_MULTI_QUEUE_MUTEX_UNLOCK(mq);
    return ret;
  }
  sq->active_flushing = TRUE;
  GST_MULTI_QUEUE_MUTEX_UNLOCK(mq);

  GST_INFO_OBJECT(mq, "flush single queue %d", sq->id);

  flush_start_event = gst_event_new_flush_start ();
  GST_INFO_OBJECT(mq, "send flush start event %p to downstream",
     flush_start_event);
  if (flush_start_event) {
    ret = gst_pad_push_event(sq->srcpad, flush_start_event);
  } else {
    ret = FALSE;
  }
  GST_INFO_OBJECT(mq, "send flush start to downstream ret %d", ret);

  flush_stop_event = gst_event_new_flush_stop ((gboolean)FALSE);
  GST_INFO_OBJECT(mq, "send flush stop event %p to downstream",
      flush_stop_event);
  if(flush_stop_event) {
    ret = gst_pad_push_event(sq->srcpad, flush_stop_event);
  } else {
    ret = FALSE;
  }
  GST_INFO_OBJECT(mq, "send flush stop to downstream ret %d", ret);

#if 0
  gst_segment_init (&segment, GST_FORMAT_TIME);
  segment.position = sq->src_segment.position;
  segment.time = sq->src_segment.position;
  segment.start = sq->src_segment.position;
  segment_event =  gst_event_new_segment (&segment);
  GST_INFO_OBJECT(mq, "send segment event %p to downstream",
      segment_event);
  if(segment_event) {
    ret = gst_pad_push_event(sq->srcpad, segment_event);
  } else {
    ret = FALSE;
  }
  GST_INFO_OBJECT(mq, "send segment event downstream ret %d", ret);
#endif

  GST_MULTI_QUEUE_MUTEX_LOCK(mq);
  sq->active_transiting = FALSE;
  GST_MULTI_QUEUE_MUTEX_UNLOCK(mq);

  return ret;
}


static gboolean
gst_single_queue_wait_running_time(GstMultiQueue *mq,
    GstSingleQueue *sq,
    GstBuffer *buf)
{
  GstClockTime running_time;
  GstSegment *seg;
  GstClock *clock;
  gint64 cur_running_time;
  GstSegment *active_seg;
  GstSingleQueue *active_sq;

  seg = &sq->src_segment;

  GST_MULTI_QUEUE_MUTEX_LOCK (mq);

  running_time = GST_BUFFER_TIMESTAMP (buf);
  /* If possible try to get the running time at the end of the buffer */
  if (GST_BUFFER_DURATION_IS_VALID (buf))
    running_time += GST_BUFFER_DURATION (buf);
  /* Only use the segment to convert to running time if the segment is
   * in TIME format, otherwise do our best to try to sync */
  if (GST_CLOCK_TIME_IS_VALID (seg->stop)) {
    if (running_time > seg->stop) {
      running_time = seg->stop;
    }
  }
  running_time =
      gst_segment_to_running_time (seg, GST_FORMAT_TIME, running_time);
  /* If this is outside the segment don't sync */
  if (running_time == -1) {
    GST_DEBUG_OBJECT (mq,
      "Not waiting because buffer is outside segment");
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
    return FALSE;
  }

  while (TRUE) {
    if (!mq->active_audio_pad) {
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      GST_DEBUG_OBJECT (mq, "there is no active audio pad");
      return FALSE;
    }
    active_sq = gst_pad_get_element_private (mq->active_audio_pad);

    clock = gst_element_get_clock (GST_ELEMENT_CAST (mq));
    if (clock) {
      GstClockTime base_time;

      cur_running_time = gst_clock_get_time (clock);
      base_time = gst_element_get_base_time (GST_ELEMENT_CAST (mq));
      if (base_time <= cur_running_time)
        cur_running_time -= base_time;
      else
        cur_running_time = 0;

      gst_object_unref (clock);
    } else {
      active_seg = &sq->src_segment;

      /* If the active segment is configured but not to time format
       * we can't do any syncing at all */
      if (active_seg->format != GST_FORMAT_TIME) {
        GST_INFO_OBJECT (mq,
            "Not waiting because active segment isn't in TIME format");
        GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
        return FALSE;
      }

      /* Get active pad's running time, if no configured segment yet keep at -1 */
      if (active_seg->format == GST_FORMAT_TIME)
        cur_running_time = gst_segment_to_running_time (active_seg,
                               GST_FORMAT_TIME, active_seg->position);
    }

    /* wait until
     * 1) this is the active pad
     * 2) the pad is flushing
     * 3) the buffer running time is before current running time
     * 4) active pad is not end
     */
    GST_DEBUG_OBJECT (mq, "sq id %d, active %d, flushing %d"
        ", active pad %id, srcresult %s"
        ", running_time %" GST_TIME_FORMAT
        ", cur_running_time %" GST_TIME_FORMAT,
        sq->id, sq->is_active, sq->flushing,
        active_sq->id, gst_flow_get_name(active_sq->srcresult),
        GST_TIME_ARGS(running_time),
        GST_TIME_ARGS(cur_running_time));

    if (!sq->is_active && !sq->flushing &&
        active_sq->srcresult != GST_FLOW_EOS &&
        (running_time >= cur_running_time)) {
      GST_MULTI_QUEUE_WAIT(mq);
    } else {
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);
      break;
    }
  }

  return TRUE;
}
