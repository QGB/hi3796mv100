cmd_arch/arm/boot/dts/hi3798mv100.dtb := mkdir -p arch/arm/boot/dts/ ; arm-histbv310-linux-gcc -E -Wp,-MD,arch/arm/boot/dts/.hi3798mv100.dtb.d.pre.tmp -nostdinc -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/boot/dts -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/boot/dts/include -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/drivers/of/testcase-data -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/boot/dts/.hi3798mv100.dtb.dts.tmp /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/boot/dts/hi3798mv100.dts ; ./scripts/dtc/dtc -O dtb -o arch/arm/boot/dts/hi3798mv100.dtb -b 0 -i /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/boot/dts/  -d arch/arm/boot/dts/.hi3798mv100.dtb.d.dtc.tmp arch/arm/boot/dts/.hi3798mv100.dtb.dts.tmp ; cat arch/arm/boot/dts/.hi3798mv100.dtb.d.pre.tmp arch/arm/boot/dts/.hi3798mv100.dtb.d.dtc.tmp > arch/arm/boot/dts/.hi3798mv100.dtb.d

source_arch/arm/boot/dts/hi3798mv100.dtb := /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/boot/dts/hi3798mv100.dts

deps_arch/arm/boot/dts/hi3798mv100.dtb := \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/boot/dts/include/dt-bindings/clock/hi3798mv100-clock.h \

arch/arm/boot/dts/hi3798mv100.dtb: $(deps_arch/arm/boot/dts/hi3798mv100.dtb)

$(deps_arch/arm/boot/dts/hi3798mv100.dtb):
