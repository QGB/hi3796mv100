LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := pkg_xml2

EXT_TYPE_GZ := tar.gz
#EXT_TYPE_XZ := tar.xz
PKG_XML2_NAME := libxml2-2.9.3


LOCAL_INTERMEDIATE_TARGETS := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE) \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE)_prepare \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE)_configure \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE)_make \
	$(LOCAL_MODULE)-clean

PRIVATEPKG_XML2_NAMEPREPARE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE)_prepare
PRIVATEPKG_XML2_NAMECONFIGURE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE)_configure
PRIVATEPKG_XML2_NAMEMAKE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE)_make
PRIVATEPKG_XML2_NAMEINSTALL := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE)_install
ifeq ($(ENV_SME_VERSION_TYPE), rls)
$(PRIVATEPKG_XML2_NAMECONFIGURE): PRIVATE_PKG_XML2_DBG_FLG := --disable-debug
else
$(PRIVATEPKG_XML2_NAMECONFIGURE): PRIVATE_PKG_XML2_DBG_FLG := --enable-debug
endif

$(LOCAL_MODULE)-deps:$(LOCAL_MODULE)
$(LOCAL_MODULE):$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE)

$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/.$(LOCAL_MODULE):$(PRIVATEPKG_XML2_NAMEINSTALL)

$(PRIVATEPKG_XML2_NAMEINSTALL):$(PRIVATEPKG_XML2_NAMEMAKE)
	$(NS)echo "begin INSTALL $(PKG_XML2_NAME)!"
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libxml2.so* $(TARGET_OUT_LIB_DIR)/
	#cp -af $(THIRDPARTY_OBJ_DIR)/lib/libxml2.so* $(TARGET_OUT_LIB_DIR)/libxml2.so
	#cp -af $(THIRDPARTY_OBJ_DIR)/lib/libxml2.so.2 $(TARGET_OUT_LIB_DIR)/libxml2.so.2
	#cp -af $(THIRDPARTY_OBJ_DIR)/lib/libxml2.so.2.9.3 $(TARGET_OUT_LIB_DIR)/libxml2.so.2.9.3
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libxml2.so
endif
	$(NS)echo "end INSTALL $(PKG_XML2_NAME)!"

$(PRIVATEPKG_XML2_NAMEMAKE):$(PRIVATEPKG_XML2_NAMECONFIGURE)
	$(NS)echo "begin make $(PKG_XML2_NAME)!"
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME) $(MAKE_PARALLEL)
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME) install $(MAKE_PARALLEL)
	$(NS)echo "end make $(PKG_XML2_NAME)!"

$(PRIVATEPKG_XML2_NAMECONFIGURE):$(PRIVATEPKG_XML2_NAMEPREPARE)
	$(NS)echo "begin configure $(PKG_XML2_NAME)..."
	chmod 777 $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)/configure
	cd $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME);ac_cv_path_install="/usr/bin/install -cp" ./configure --prefix="${THIRDPARTY_OBJ_DIR}" \
		--host=$(CFG_HOST_TYPE) \
		CFLAGS="$(OPENSOURCE_CFLAGS) --sysroot=$(CFG_COMPILE_SYSROOT)" \
		CPPFLAGS="$(OPENSOURCE_CXXFLAGS)" \
		LDFLAGS="$(OPENSOURCE_LDFLAGS)" \
                --without-lzma \
		--disable-static --enable-shared --without-python $(PRIVATE_PKG_XML2_DBG_FLG) \
		CXX=$(TARGET_CXX) CC=$(TARGET_CC)
	$(NS)touch $@
	$(NS)echo "end configure $(PKG_XML2_NAME)..."

$(PRIVATEPKG_XML2_NAMEPREPARE):
	$(NS)echo "begin prepare $(PKG_XML2_NAME)..."
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)
	$(NC)mkdir -p $(SME_THIRDPARTY_MERGE_DIR)
	tar -xf $(SME_THIRDPARTY_ORG_DIR)/$(PKG_XML2_NAME).$(EXT_TYPE_GZ) -C $(SME_THIRDPARTY_MERGE_DIR)
	$(NC)cp -af $(SME_THIRDPARTY_PATCH_DIR)/$(PKG_XML2_NAME) $(SME_THIRDPARTY_MERGE_DIR)/
	$(NS)touch $@
	$(NS)echo "end prepare $(PKG_XML2_NAME)!"

$(LOCAL_MODULE)-clean:
	$(NS)echo "begin make clean $(PKG_XML2_NAME) ..."
	$(NC)rm -rf $(PRIVATEPKG_XML2_NAMECONFIGURE)
	$(NC)rm -rf $(PRIVATEPKG_XML2_NAMEPREPARE)
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libxml2.so
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libxml2.so.2
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libxml2.so.2.9.3
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME) uninstall $(MAKE_PARALLEL)
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME) clean $(MAKE_PARALLEL)
	$(NS)echo "end make clean $(PKG_XML2_NAME)"

$(LOCAL_MODULE)-cfg-clean:
	$(NS)echo "begin make clean $(PKG_XML2_NAME)-cfg ..."
	$(NC)rm -rf $(PRIVATEPKG_XML2_NAMECONFIGURE)
	$(NS)echo "end make clean $(PKG_XML2_NAME)-cfg ..."

$(LOCAL_MODULE)-prepare-clean:$(LOCAL_MODULE)-clean
	$(NS)echo "begin make clean $(PKG_XML2_NAME)-prepare ..."
	$(NC)rm -rf $(PRIVATEPKG_XML2_NAMECONFIGURE)
	$(NC)rm -rf $(PRIVATEPKG_XML2_NAMEPREPARE)
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_XML2_NAME)
	$(NS)echo "end make clean $(PKG_XML2_NAME)-prepare ..."

include $(BUILD_OPENSOURCE_PKG)
