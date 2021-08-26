###########################################################
#cfg.mk
#���б�����CFG_��ͷ
#ע����������治���пո�
###########################################################
#for linux
#$(info ### CURDIR ###: $(CURDIR))

ifeq ($(MEDIAOS_DIR_STRUCTURE),y)
    SDK_DIR ?= $(shell cd $(CURDIR)/../../HiSTBLinux/Code/ && /bin/pwd)
else
    SDK_DIR ?= $(shell cd $(CURDIR)/../../../../../ && /bin/pwd)
endif
-include $(SDK_DIR)/base.mak
#$(info ### CFG_HI_CHIP_TYPE ###: $(CFG_HI_CHIP_TYPE))
############ begin define switchs ############################
#���ر�����������Ŀ�Ӿ����������
#if one module or feature defines CFG_XXX item, but not set the CFG_XX item val,
#just as set the val to "n"

#ndk tool cfg item, val below:
#"y":use ndk to build sme,currently used in android
#"n":do not use ndk to build sme
CFG_ENABLE_NDK=n

#multi-audio track feature cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_MULTI_AUDIO_TRACK=y

#huawei secure function cfg item, val below:
#"y":enable
#"n":disable
#"p":prebuilt
CFG_ENABLE_HWSECURE=p

#multiqueue element cfg item, val below:
#y:use sme-modifyed
#n:donot use sme-modifyed
CFG_ENABLE_SME_MQ_CTRL=y

#audio pass-through feature cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_BITSTREAM=n

#dra audio decoder cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_DRA_DECODER=n

#dvb feature cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_DVB=n

#dvbplaybin feature cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_DVBPLAYBIN=n

#subtitle feature cfg item, val below:
#"y":enable
#"n":disable
#if not set this item,just as set the val to "n"
CFG_ENABLE_SUBTITLE_PATH=n

#Hisi charset dectect used for subtitle cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_HI_CHARSET_DETECT=n

#source
#sme httpsrc_soup plugin cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_SME_HTTPSRC_SOUP=y

#protocol
#gst-bad-plugins hls plugin cfg item, val below:
#"y":enable and compile from source code
#"p":enable and compile from prebuilt
#"n":disable
CFG_ENABLE_GST_BAD_HLS=y

#gst-bad-plugins dash plugin cfg item, val below:
#"y":enable and compile from source code
#"p":enable and compile from prebuilt
#"n":disable
CFG_ENABLE_GST_BAD_DASH=p

#demux
#ffmpeg lib cfg item, val below:
#"y":enable and compile from source code
#"p":enable and compile from prebuilt
#"n":disable
CFG_ENABLE_FFMPEG=p

#ffmpeg protocol
#use ffmpeg protocol, val below:
#"y":enable and compile source and demuxer element from source code
#"n":disable
CFG_ENABLE_FFMPEG_PROTOCOL=y

#dvb gsttsdmx plugin cfg item, val below:
#"y":enable and compile the linux version
#"n":enable and compile the android version
CFG_ENABLE_DEMUX_DVB_LINUX=n

#av dec
#adec_ffmpeg plugin cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_ADEC_FFMPEG=y

#gstomx plugin cfg item, val below:
#"y":enable and compile from source code
#"p":enable and compile from prebuilt
#"n":disable
CFG_ENABLE_GSTOMX=y

#audio sink element
#asink_af plugin cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_ASINK_AF=n

#asink_hisi_hal plugin cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_ASINK_HISI_HAL=y

#asink_hisi_unf plugin cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_ASINK_HISI_UNF=n

#asink_alsa plugin cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_ALSASINK=n

#ddp audio passthrough only support
#"y":enable
#"n":disable
CFG_ENABLE_DDP_PASSTHROUGH_ONLY_SUPPORT=n

#vsink element
#vsink_hisi_mpi plugin cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_HISI_MPI_VSINK=n

#vsink_hisi_hal plugin cfg item, val below:
#"y":enable and compile from source code
#"p":enable and compile from prebuilt
#"n":disable
CFG_ENABLE_VSINKHIHAL=y

CFG_ENABLE_ACODEC_PCM_BLURAY=y
CFG_ENABLE_ACODEC_WMA_PRO=y

#benchmark
CFG_ENABLE_BENCHMARK=y
############ end define switchs ##############################

############ begin define vars ############################
#���붨��
#project name
CFG_PROJECT_NAME=HiSTBLinux.$(CFG_HI_CHIP_TYPE)

#version
#CFLAGS_MACRO += -D DBG_VER=\"debug\"
#CFLAGS_MACRO += -D PRODUCT=\"HISI\"
#CFLAGS_MACRO += -D OSVER=\"linux\"
#CFLAGS_MACRO += -D CPU=\"hi3798m\"
#CFLAGS_MACRO += -D CPUBIT=\"32\"
ifeq ($(ENV_SME_VERSION_TYPE), rls)
	CFG_SME_VERSION=HiSTBLinux\ \(SME3.0\)\ release\ version\ HISI/linux/$(CFG_HI_CHIP_TYPE)/32b
else
	CFG_SME_VERSION=HiSTBLinux\ \(SME3.0\)\ debug\ version\ HISI/linux/$(CFG_HI_CHIP_TYPE)/32b
endif

#toolchain name
CFG_TOOLCHAINS_NAME=arm-histbv310-linux

#��Դ�����������������е�ƽ̨
CFG_HOST_TYPE=arm-histbv310-linux

#toolchain sysroot
#�����ndk��ô����Ҫ����sysroot����config.mk�ж���
ifneq ($(CFG_ENABLE_NDK), y)
CFG_COMPILE_SYSROOT=/opt/hisi-linux/x86-arm/arm-histbv310-linux/target
else
CFG_COMPILE_SYSROOT=
endif

##########begin ���Ŀ¼����###############################
#���������TOPDIR(MediaOS),��CFG_RT��ʼ
#ע����TVOS��Ŀ¼�ṹ��mediaos��Ŀ¼�ṹ���б仯�ģ���envsetup.sh�ж���MEDIAOS_DIR_STRUCTURE=yΪmediaosĿ¼��
ifeq ($(MEDIAOS_DIR_STRUCTURE),y)
    #SME������ƽ̨SDK·�������TOPDIRĿ¼
    CFG_RT_PLATFORM_SDK_DIR=HiSTBLinux
else
    CFG_RT_PLATFORM_SDK_DIR=../../../..
endif

#SME ������hisi SDK��·����
CFG_RT_HI_SDK_DIR=$(CFG_RT_PLATFORM_SDK_DIR)/Code

#SME������ƽ̨SDKͷ�ļ�·�������TOPDIRĿ¼
CFG_RT_PLATFORM_SDK_INC_DIR= \
	$(CFG_RT_HI_SDK_DIR)/hal/include \
	$(CFG_RT_HI_SDK_DIR)/sample/common \
	$(CFG_RT_HI_SDK_DIR)/source/msp/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/higo/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/tde/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/drv/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/drv/mce \
	$(CFG_RT_HI_SDK_DIR)/source/common/include \
	$(CFG_RT_HI_SDK_DIR)/source/common/api/include \
	$(CFG_RT_HI_SDK_DIR)/source/common/drv/include \
	$(CFG_RT_HI_SDK_DIR)/source/common/api/mmz \
	$(CFG_RT_HI_SDK_DIR)/source/component/zlib/include \
	$(CFG_RT_HI_SDK_DIR)/source/component/ha_codec/include \

#SME������ƽ̨SDK��̬��·�������TOPDIRĿ¼
CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR=$(CFG_RT_PLATFORM_SDK_DIR)/Code/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)/lib/share/

#SME omx��Դ���������OMXͷ�ļ�Ŀ¼�����TOPDIRĿ¼
CFG_RT_OMX_H_DIR=$(CFG_RT_HI_SDK_DIR)/source/msp/api/omx/include
CFG_RT_OMX_PRIVATE_H=$(CFG_RT_HI_SDK_DIR)/source/msp/api/omx/omx_audio/common/base \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/omx/omx_audio/common/omx_ha/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/omx/omx_audio/common/osal

ifeq ($(CFG_ENABLE_ALSASINK),y)
#alsa ͷ�ļ�·�������SME
CFG_RT_ALSA_INC_DIR=$(CFG_RT_PLATFORM_SDK_DIR)/pub/include/alsa_bluez
CFG_RT_ALSA_LIB_DIR=$(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR)/alsa_bluez
#libasound.so,ȥ��lib��ȥ��.so
CFG_ALSA_LIB_NAME=asound
endif

#audiosink element name
CFG_AUDIOSINK_NAME=smeaudiosink_hihal

#videosink element name
CFG_VIDEOSINK_NAME=smevideosink_hihal

ifeq ($(CFG_ENABLE_HI_CHARSET_DETECT),y)
#libhi_charsetMgr.so,ȥ��lib��ȥ��.so
CFG_HI_CHARSETMGR_LIB_NAME=hi_charsetMgr
endif
##########end ���Ŀ¼����###############################

#ͨ�ú�
CFG_COMMON_MACRO=-D__LINUX__ -DGST_SME_BENCHMARK -DLOG_IN_FILE -DLINUX_OS
CFG_COMMON_MACRO += -D_LARGEFILE64_SOURCE
CFG_COMMON_MACRO += -DGST_SME_NO_LOGCAT
ifeq ($(CFG_HI_CHIP_TYPE),hi3798cv200)
CFG_COMMON_MACRO += -D__HI3798CV200__
endif
ifeq ($(CFG_ENABLE_BITSTREAM), y)
CFG_COMMON_MACRO += -D__DDP_PT__
endif

ifeq ($(CFG_ENABLE_ACODEC_PCM_BLURAY), y)
CFG_COMMON_MACRO += -D__ENABLE_ACODEC_PCM_BLURAY__
endif
ifeq ($(CFG_ENABLE_ACODEC_WMA_PRO), y)
CFG_COMMON_MACRO += -D__ENABLE_ACODEC_WMA_PRO__
endif


############ end define vars ##############################
