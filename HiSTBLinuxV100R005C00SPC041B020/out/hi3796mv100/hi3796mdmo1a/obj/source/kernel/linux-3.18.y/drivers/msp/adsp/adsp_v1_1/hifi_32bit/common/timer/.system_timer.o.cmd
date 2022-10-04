cmd_drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.o := arm-histbv310-linux-gcc -Wp,-MD,drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/.system_timer.o.d  -nostdinc -isystem /home/qgb/github/hi3798mv100/HiSTBLinuxV100R005C00SPC041B020/tools/linux/toolchains/arm-histbv310-linux/bin/../lib/gcc/arm-gcc49-linux-gnueabi/4.9.2/include -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include -Iarch/arm/include/generated  -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include -Iinclude -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi -Iinclude/generated/uapi -include /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/mach-hi3798mx/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -mfpu=vfp -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -include asm/unified.h -msoft-float   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/common/drv/include -DMODULE  -c -o drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.o /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.S

source_drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.o := /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.S

deps_drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.o := \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/common/drv/include/hi_asm_define.h \
    $(wildcard include/config/arm/unwind.h) \
    $(wildcard include/config/remove/string.h) \
    $(wildcard include/config/arch/lp64/mode.h) \

drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.o: $(deps_drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.o)

$(deps_drivers/msp/adsp/adsp_v1_1/./hifi_32bit/common/timer/system_timer.o):
