LOCAL_PATH := $(my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libsme_gstplg_dvbplaybin

LOCAL_SRC_FILES := gstsmedvbplaybin.c

LOCAL_CFLAGS += $(EXTRA_CFLAGS) -DHAVE_CONFIG_H
LOCAL_CPPFLAGS += $(EXTRA_CXXFLAGS) -DHAVE_CONFIG_H

LOCAL_C_INCLUDES := $(TOPDIR)/$(CFG_RT_SME_THIRDPARTY_MERGE_DIR)/gstreamer-1.2.3 \
	$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/include/gstreamer-1.0 \
	$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/include/gstreamer-1.0/gst \
	$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/include/glib-2.0 \
	$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/include/glib-2.0/glib \
	$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/include/glib-2.0/gio \
	$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/lib/glib-2.0/include \
	$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/include/glib-2.0/glib/gobject

LOCAL_C_INCLUDES += $(TOPDIR)/source/sme/source/plugins/common \
	$(TOPDIR)/source/sme/source/common/inc \
	$(TOPDIR)/source/sme/source/osal/inc \
	$(TOPDIR)/source/sme/api

LOCAL_LDLIBS += $(EXTRA_LDLIBS)
LOCAL_LDLIBS += -L$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/lib \
    -lgstreamer-1.0  -lgstbase-1.0 \
	-lglib-2.0 -lgobject-2.0 \
	-lgmodule-2.0 -lgio-2.0 \
	-lgstpbutils-1.0

LOCAL_SHARED_LIBRARIES := libsme_osal libsme_common libsme_gst_common libsme_gst_ptscalibrate
LOCAL_REQUIRED_MODULES := libsme_osal libsme_common libsme_gst_common libsme_gst_ptscalibrate

LOCAL_MODULE_PATH := $(TARGET_OUT_PLUGIN_DIR)

include $(BUILD_SHARED_LIBRARY)