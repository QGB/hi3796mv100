cmd_drivers/msp/advca/runtime/sha1.o := arm-histbv310-linux-gcc -Wp,-MD,drivers/msp/advca/runtime/.sha1.o.d  -nostdinc -isystem /home/qgb/github/hi3798mv100/HiSTBLinuxV100R005C00SPC041B020/tools/linux/toolchains/arm-histbv310-linux/bin/../lib/gcc/arm-gcc49-linux-gnueabi/4.9.2/include -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include -Iarch/arm/include/generated  -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include -Iinclude -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi -Iinclude/generated/uapi -include /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/kconfig.h  -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/drivers/msp/advca -Idrivers/msp/advca -D__KERNEL__ -mlittle-endian   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/mach-hi3798mx/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fno-ipa-sra -mabi=aapcs-linux -mno-thumb-interwork -mfpu=vfp -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -O2 --param=allow-store-data-races=0 -Wframe-larger-than=1024 -fstack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -DCC_HAVE_ASM_GOTO -Werror -z relro -DCHIP_TYPE_hi3796mv100 -DSDK_VERSION="HiSTBLinuxV100R005C00SPC041B020_20161028" -DHI_GPIOI2C_SUPPORT -DHI_LOG_SUPPORT=1 -DHI_LOG_LEVEL=4 -DHI_PROC_SUPPORT=1 -DHI_HDMI_SUPPORT_1_4 -DHI_KEYLED_SUPPORT -DHI_HDCP_SUPPORT -DHI_SCI_SUPPORT -DHI_PVR_SUPPORT -DHI_VI_SUPPORT -DHI_VENC_SUPPORT -DHI_AENC_SUPPORT -DHI_PQ_V3_0   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/common/include   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/common/api/include   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/common/drv/include   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/msp/include   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/msp/api/include   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/msp/drv/include   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/msp/drv/advca   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/msp/drv/advca/runtime   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/msp/drv/advca/V300   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/msp/drv/advca/ca_otp   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/msp/drv/advca/ca_otp/ca_otpv200 -DDDR_WAKEUP_SRC=\"ddr_wakeup_check/output_32.txt\"  -DMODULE  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(sha1)"  -D"KBUILD_MODNAME=KBUILD_STR(hi_advca)" -c -o drivers/msp/advca/runtime/sha1.o /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/drivers/msp/advca/runtime/sha1.c

source_drivers/msp/advca/runtime/sha1.o := /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/drivers/msp/advca/runtime/sha1.c

deps_drivers/msp/advca/runtime/sha1.o := \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/drivers/msp/advca/runtime/sha1.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/64bit.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/linux/types.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/types.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/int-ll64.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitsperlong.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/asm-generic/bitsperlong.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/linux/posix_types.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/stddef.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/linux/stddef.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi/asm/posix_types.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/asm-generic/posix_types.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
  /home/qgb/github/hi3798mv100/HiSTBLinuxV100R005C00SPC041B020/tools/linux/toolchains/arm-histbv310-linux/lib/gcc/arm-gcc49-linux-gnueabi/4.9.2/include/stdarg.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/linux/string.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/string.h \

drivers/msp/advca/runtime/sha1.o: $(deps_drivers/msp/advca/runtime/sha1.o)

$(deps_drivers/msp/advca/runtime/sha1.o):
