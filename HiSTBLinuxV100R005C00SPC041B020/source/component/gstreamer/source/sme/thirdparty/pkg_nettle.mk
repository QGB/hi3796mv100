LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := pkg_nettle

EXT_TYPE_GZ := tar.gz
#EXT_TYPE_XZ := tar.xz
PKG_NETTLE_NAME := nettle-2.7.1


LOCAL_INTERMEDIATE_TARGETS := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE) \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE)_prepare \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE)_configure \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE)_make \
	$(LOCAL_MODULE)-clean

PRIVATE_PKG_NETTLE_NAME_PREPARE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE)_prepare
PRIVATE_PKG_NETTLE_NAME_CONFIGURE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE)_configure
PRIVATE_PKG_NETTLE_NAME_MAKE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE)_make
PRIVATE_PKG_NETTLE_NAME_INSTALL := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE)_install

$(LOCAL_MODULE)-deps:$(LOCAL_MODULE)
$(LOCAL_MODULE):$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE)

$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/.$(LOCAL_MODULE):$(PRIVATE_PKG_NETTLE_NAME_INSTALL)

$(PRIVATE_PKG_NETTLE_NAME_INSTALL):$(PRIVATE_PKG_NETTLE_NAME_MAKE)
	$(NS)echo "begin INSTALL $(PKG_NETTLE_NAME)!"
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libnettle.so $(TARGET_OUT_LIB_DIR)/libnettle.so
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libnettle.so.4 $(TARGET_OUT_LIB_DIR)/libnettle.so.4
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libnettle.so.4.7 $(TARGET_OUT_LIB_DIR)/libnettle.so.4.7
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libnettle.so.4.7
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libhogweed.so $(TARGET_OUT_LIB_DIR)/libhogweed.so
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libhogweed.so.2 $(TARGET_OUT_LIB_DIR)/libhogweed.so.2
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libhogweed.so.2.5 $(TARGET_OUT_LIB_DIR)/libhogweed.so.2.5
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libhogweed.so.2.5
endif
	$(NS)echo "end INSTALL $(PKG_NETTLE_NAME)!"

$(PRIVATE_PKG_NETTLE_NAME_MAKE):$(PRIVATE_PKG_NETTLE_NAME_CONFIGURE)
	$(NS)echo "begin make $(PKG_NETTLE_NAME)!"
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME) $(MAKE_PARALLEL)
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME) install $(MAKE_PARALLEL)
	$(NS)echo "end make $(PKG_NETTLE_NAME)!"

$(PRIVATE_PKG_NETTLE_NAME_CONFIGURE):$(PRIVATE_PKG_NETTLE_NAME_PREPARE)
	$(NS)echo "begin configure $(PKG_NETTLE_NAME)..."
	chmod 777 $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)/configure
	cd $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME);ac_cv_path_install="/usr/bin/install -cp" ./configure --prefix="${THIRDPARTY_OBJ_DIR}" \
		--host=$(CFG_HOST_TYPE) \
		CFLAGS="$(OPENSOURCE_CFLAGS) -I$(THIRDPARTY_OBJ_DIR)/include --sysroot=$(CFG_COMPILE_SYSROOT)" \
		CXXFLAGS="$(OPENSOURCE_CXXFLAGS) -I$(THIRDPARTY_OBJ_DIR)/include" \
		LDFLAGS="$(OPENSOURCE_LDFLAGS) -L$(THIRDPARTY_OBJ_DIR)/lib" \
		--enable-static --enable-shared --enable-public-key \
		CXX=$(TARGET_CXX) CC=$(TARGET_CC)
	$(NS)touch $@
	$(NS)echo "end configure $(PKG_NETTLE_NAME)..."

$(PRIVATE_PKG_NETTLE_NAME_PREPARE):
	$(NS)echo "begin prepare $(PKG_NETTLE_NAME)..."
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)
	$(NC)mkdir -p $(SME_THIRDPARTY_MERGE_DIR)
	tar -xf $(SME_THIRDPARTY_ORG_DIR)/$(PKG_NETTLE_NAME).$(EXT_TYPE_GZ) -C $(SME_THIRDPARTY_MERGE_DIR)
	$(NC)cp -af $(SME_THIRDPARTY_PATCH_DIR)/$(PKG_NETTLE_NAME) $(SME_THIRDPARTY_MERGE_DIR)/
	$(NS)touch $@
	$(NS)echo "end prepare $(PKG_NETTLE_NAME)!"

$(LOCAL_MODULE)-clean:
	$(NS)echo "begin make clean $(PKG_NETTLE_NAME) ..."
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libnettle.so
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libnettle.so.4
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libnettle.so.4.7
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libhogweed.so
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libhogweed.so.2
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libhogweed.so.2.5
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME) uninstall $(MAKE_PARALLEL)
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME) clean $(MAKE_PARALLEL)
	$(NS)echo "end make clean $(PKG_NETTLE_NAME)"

$(LOCAL_MODULE)-cfg-clean:
	$(NS)echo "begin make clean $(PKG_NETTLE_NAME)-cfg ..."
	$(NC)rm -rf $(PRIVATE_PKG_NETTLE_NAME_CONFIGURE)
	$(NS)echo "end make clean $(PKG_NETTLE_NAME)-cfg ..."

$(LOCAL_MODULE)-prepare-clean:$(LOCAL_MODULE)-clean
	$(NS)echo "begin make clean $(PKG_NETTLE_NAME)-prepare ..."
	$(NC)rm -rf $(PRIVATE_PKG_NETTLE_NAME_CONFIGURE)
	$(NC)rm -rf $(PRIVATE_PKG_NETTLE_NAME_PREPARE)
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_NETTLE_NAME)
	$(NS)echo "end make clean $(PKG_NETTLE_NAME)-prepare ..."

include $(BUILD_OPENSOURCE_PKG)
