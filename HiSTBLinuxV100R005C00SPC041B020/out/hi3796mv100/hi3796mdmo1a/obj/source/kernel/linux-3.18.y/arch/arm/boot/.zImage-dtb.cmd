cmd_arch/arm/boot/zImage-dtb := (cat arch/arm/boot/zImage arch/arm/boot/dts/hi3798mv100.dtb > arch/arm/boot/zImage-dtb) || (rm -f arch/arm/boot/zImage-dtb; false)
