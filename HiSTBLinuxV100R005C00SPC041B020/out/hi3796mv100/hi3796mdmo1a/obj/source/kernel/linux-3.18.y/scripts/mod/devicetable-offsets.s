	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 2	@ Tag_ABI_enum_size
	.eabi_attribute 30, 2	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 0	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 4	@ Tag_ABI_PCS_wchar_t
	.file	"devicetable-offsets.c"
@ GNU C (gcc-4.9.2 + glibc-2.22 (Build by czyong) Wed Mar  9 16:30:48 CST 2016) version 4.9.2 20140904 (prerelease) (arm-gcc49-linux-gnueabi)
@	compiled by GNU C version 4.1.2 20080704 (Red Hat 4.1.2-44), GMP version 5.0.5, MPFR version 3.1.2, MPC version 1.0.1
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed:  -nostdinc
@ -I /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include
@ -I arch/arm/include/generated
@ -I /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include
@ -I include
@ -I /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi
@ -I arch/arm/include/generated/uapi
@ -I /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi
@ -I include/generated/uapi
@ -I /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod
@ -I scripts/mod
@ -I /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/mach-hi3798mx/include
@ -iprefix /home/qgb/github/hi3798mv100/HiSTBLinuxV100R005C00SPC041B020/tools/linux/toolchains/arm-histbv310-linux/bin/../lib/gcc/arm-gcc49-linux-gnueabi/4.9.2/
@ -isysroot /home/qgb/github/hi3798mv100/HiSTBLinuxV100R005C00SPC041B020/tools/linux/toolchains/arm-histbv310-linux/bin/../target
@ -D __KERNEL__ -D __LINUX_ARM_ARCH__=7 -U arm -D CC_HAVE_ASM_GOTO
@ -D KBUILD_STR(s)=#s -D KBUILD_BASENAME=KBUILD_STR(devicetable_offsets)
@ -D KBUILD_MODNAME=KBUILD_STR(devicetable_offsets)
@ -isystem /home/qgb/github/hi3798mv100/HiSTBLinuxV100R005C00SPC041B020/tools/linux/toolchains/arm-histbv310-linux/bin/../lib/gcc/arm-gcc49-linux-gnueabi/4.9.2/include
@ -include /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/kconfig.h
@ -MD scripts/mod/.devicetable-offsets.s.d
@ /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -mfpu=vfp -marm -march=armv7-a -mfloat-abi=soft
@ -mtls-dialect=gnu -mno-unaligned-access -mword-relocations
@ -auxbase-strip scripts/mod/devicetable-offsets.s -O2 -Wall -Wundef
@ -Wstrict-prototypes -Wno-trigraphs -Werror=implicit-function-declaration
@ -Wno-format-security -Wframe-larger-than=1024
@ -Wno-unused-but-set-variable -Wdeclaration-after-statement
@ -Wno-pointer-sign -Werror=implicit-int -Werror=strict-prototypes
@ -std=gnu90 -p -fno-strict-aliasing -fno-common -fno-dwarf2-cfi-asm
@ -fno-ipa-sra -funwind-tables -fstack-protector -fno-omit-frame-pointer
@ -fno-optimize-sibling-calls -fno-var-tracking-assignments
@ -fno-strict-overflow -fconserve-stack -fverbose-asm
@ -fno-delete-null-pointer-checks -fdiagnostics-color=auto
@ -fno-aggressive-loop-optimizations -fno-tree-vrp
@ --param allow-store-data-races=0
@ options enabled:  -fauto-inc-dec -fbranch-count-reg -fcaller-saves
@ -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
@ -fcrossjumping -fcse-follow-jumps -fdefer-pop -fdevirtualize
@ -fdevirtualize-speculatively -fearly-inlining
@ -feliminate-unused-debug-types -fexpensive-optimizations
@ -fforward-propagate -ffunction-cse -fgcse -fgcse-lm -fgnu-runtime
@ -fgnu-unique -fguess-branch-probability -fhoist-adjacent-loads -fident
@ -fif-conversion -fif-conversion2 -findirect-inlining -finline
@ -finline-atomics -finline-functions-called-once -finline-small-functions
@ -fipa-cp -fipa-profile -fipa-pure-const -fipa-reference
@ -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
@ -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
@ -fleading-underscore -fmath-errno -fmerge-constants -fmerge-debug-strings
@ -fmove-loop-invariants -foptimize-strlen -fpartial-inlining -fpeephole
@ -fpeephole2 -fprefetch-loop-arrays -fprofile -freg-struct-return
@ -freorder-blocks -freorder-functions -frerun-cse-after-loop
@ -fsched-critical-path-heuristic -fsched-dep-count-heuristic
@ -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
@ -fsched-pressure -fsched-rank-heuristic -fsched-spec
@ -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-insns
@ -fschedule-insns2 -fsection-anchors -fshow-column -fsigned-zeros
@ -fsplit-ivs-in-unroller -fsplit-wide-types -fstack-protector
@ -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
@ -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
@ -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop
@ -ftree-copyrename -ftree-cselim -ftree-dce -ftree-dominator-opts
@ -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
@ -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
@ -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
@ -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
@ -ftree-switch-conversion -ftree-tail-merge -ftree-ter -funit-at-a-time
@ -funwind-tables -fverbose-asm -fzero-initialized-in-bss -mapcs-frame
@ -marm -mglibc -mlittle-endian -mlra -mpic-data-is-text-relative
@ -mvectorize-with-neon-quad -mword-relocations

	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {fp, ip, lr, pc}	@,
	.pad #4
	.save {fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
#APP
@ 10 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_usb_device_id #24 sizeof(struct usb_device_id)	@
@ 0 "" 2
@ 11 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_match_flags #0 offsetof(struct usb_device_id, match_flags)	@
@ 0 "" 2
@ 12 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_idVendor #2 offsetof(struct usb_device_id, idVendor)	@
@ 0 "" 2
@ 13 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_idProduct #4 offsetof(struct usb_device_id, idProduct)	@
@ 0 "" 2
@ 14 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bcdDevice_lo #6 offsetof(struct usb_device_id, bcdDevice_lo)	@
@ 0 "" 2
@ 15 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bcdDevice_hi #8 offsetof(struct usb_device_id, bcdDevice_hi)	@
@ 0 "" 2
@ 16 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bDeviceClass #10 offsetof(struct usb_device_id, bDeviceClass)	@
@ 0 "" 2
@ 17 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bDeviceSubClass #11 offsetof(struct usb_device_id, bDeviceSubClass)	@
@ 0 "" 2
@ 18 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bDeviceProtocol #12 offsetof(struct usb_device_id, bDeviceProtocol)	@
@ 0 "" 2
@ 19 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bInterfaceClass #13 offsetof(struct usb_device_id, bInterfaceClass)	@
@ 0 "" 2
@ 20 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bInterfaceSubClass #14 offsetof(struct usb_device_id, bInterfaceSubClass)	@
@ 0 "" 2
@ 21 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bInterfaceProtocol #15 offsetof(struct usb_device_id, bInterfaceProtocol)	@
@ 0 "" 2
@ 22 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_usb_device_id_bInterfaceNumber #16 offsetof(struct usb_device_id, bInterfaceNumber)	@
@ 0 "" 2
@ 24 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_hid_device_id #16 sizeof(struct hid_device_id)	@
@ 0 "" 2
@ 25 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_hid_device_id_bus #0 offsetof(struct hid_device_id, bus)	@
@ 0 "" 2
@ 26 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_hid_device_id_group #2 offsetof(struct hid_device_id, group)	@
@ 0 "" 2
@ 27 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_hid_device_id_vendor #4 offsetof(struct hid_device_id, vendor)	@
@ 0 "" 2
@ 28 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_hid_device_id_product #8 offsetof(struct hid_device_id, product)	@
@ 0 "" 2
@ 30 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_ieee1394_device_id #24 sizeof(struct ieee1394_device_id)	@
@ 0 "" 2
@ 31 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ieee1394_device_id_match_flags #0 offsetof(struct ieee1394_device_id, match_flags)	@
@ 0 "" 2
@ 32 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ieee1394_device_id_vendor_id #4 offsetof(struct ieee1394_device_id, vendor_id)	@
@ 0 "" 2
@ 33 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ieee1394_device_id_model_id #8 offsetof(struct ieee1394_device_id, model_id)	@
@ 0 "" 2
@ 34 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ieee1394_device_id_specifier_id #12 offsetof(struct ieee1394_device_id, specifier_id)	@
@ 0 "" 2
@ 35 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ieee1394_device_id_version #16 offsetof(struct ieee1394_device_id, version)	@
@ 0 "" 2
@ 37 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_pci_device_id #28 sizeof(struct pci_device_id)	@
@ 0 "" 2
@ 38 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pci_device_id_vendor #0 offsetof(struct pci_device_id, vendor)	@
@ 0 "" 2
@ 39 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pci_device_id_device #4 offsetof(struct pci_device_id, device)	@
@ 0 "" 2
@ 40 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pci_device_id_subvendor #8 offsetof(struct pci_device_id, subvendor)	@
@ 0 "" 2
@ 41 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pci_device_id_subdevice #12 offsetof(struct pci_device_id, subdevice)	@
@ 0 "" 2
@ 42 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pci_device_id_class #16 offsetof(struct pci_device_id, class)	@
@ 0 "" 2
@ 43 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pci_device_id_class_mask #20 offsetof(struct pci_device_id, class_mask)	@
@ 0 "" 2
@ 45 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_ccw_device_id #12 sizeof(struct ccw_device_id)	@
@ 0 "" 2
@ 46 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ccw_device_id_match_flags #0 offsetof(struct ccw_device_id, match_flags)	@
@ 0 "" 2
@ 47 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ccw_device_id_cu_type #2 offsetof(struct ccw_device_id, cu_type)	@
@ 0 "" 2
@ 48 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ccw_device_id_cu_model #6 offsetof(struct ccw_device_id, cu_model)	@
@ 0 "" 2
@ 49 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ccw_device_id_dev_type #4 offsetof(struct ccw_device_id, dev_type)	@
@ 0 "" 2
@ 50 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ccw_device_id_dev_model #7 offsetof(struct ccw_device_id, dev_model)	@
@ 0 "" 2
@ 52 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_ap_device_id #8 sizeof(struct ap_device_id)	@
@ 0 "" 2
@ 53 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ap_device_id_dev_type #2 offsetof(struct ap_device_id, dev_type)	@
@ 0 "" 2
@ 55 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_css_device_id #8 sizeof(struct css_device_id)	@
@ 0 "" 2
@ 56 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_css_device_id_type #1 offsetof(struct css_device_id, type)	@
@ 0 "" 2
@ 58 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_serio_device_id #4 sizeof(struct serio_device_id)	@
@ 0 "" 2
@ 59 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_serio_device_id_type #0 offsetof(struct serio_device_id, type)	@
@ 0 "" 2
@ 60 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_serio_device_id_proto #3 offsetof(struct serio_device_id, proto)	@
@ 0 "" 2
@ 61 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_serio_device_id_id #2 offsetof(struct serio_device_id, id)	@
@ 0 "" 2
@ 62 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_serio_device_id_extra #1 offsetof(struct serio_device_id, extra)	@
@ 0 "" 2
@ 64 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_acpi_device_id #16 sizeof(struct acpi_device_id)	@
@ 0 "" 2
@ 65 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_acpi_device_id_id #0 offsetof(struct acpi_device_id, id)	@
@ 0 "" 2
@ 67 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_pnp_device_id #12 sizeof(struct pnp_device_id)	@
@ 0 "" 2
@ 68 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pnp_device_id_id #0 offsetof(struct pnp_device_id, id)	@
@ 0 "" 2
@ 70 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_pnp_card_device_id #76 sizeof(struct pnp_card_device_id)	@
@ 0 "" 2
@ 71 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pnp_card_device_id_devs #12 offsetof(struct pnp_card_device_id, devs)	@
@ 0 "" 2
@ 73 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_pcmcia_device_id #52 sizeof(struct pcmcia_device_id)	@
@ 0 "" 2
@ 74 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pcmcia_device_id_match_flags #0 offsetof(struct pcmcia_device_id, match_flags)	@
@ 0 "" 2
@ 75 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pcmcia_device_id_manf_id #2 offsetof(struct pcmcia_device_id, manf_id)	@
@ 0 "" 2
@ 76 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pcmcia_device_id_card_id #4 offsetof(struct pcmcia_device_id, card_id)	@
@ 0 "" 2
@ 77 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pcmcia_device_id_func_id #6 offsetof(struct pcmcia_device_id, func_id)	@
@ 0 "" 2
@ 78 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pcmcia_device_id_function #7 offsetof(struct pcmcia_device_id, function)	@
@ 0 "" 2
@ 79 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pcmcia_device_id_device_no #8 offsetof(struct pcmcia_device_id, device_no)	@
@ 0 "" 2
@ 80 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_pcmcia_device_id_prod_id_hash #12 offsetof(struct pcmcia_device_id, prod_id_hash)	@
@ 0 "" 2
@ 82 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_of_device_id #196 sizeof(struct of_device_id)	@
@ 0 "" 2
@ 83 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_of_device_id_name #0 offsetof(struct of_device_id, name)	@
@ 0 "" 2
@ 84 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_of_device_id_type #32 offsetof(struct of_device_id, type)	@
@ 0 "" 2
@ 85 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_of_device_id_compatible #64 offsetof(struct of_device_id, compatible)	@
@ 0 "" 2
@ 87 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_vio_device_id #64 sizeof(struct vio_device_id)	@
@ 0 "" 2
@ 88 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_vio_device_id_type #0 offsetof(struct vio_device_id, type)	@
@ 0 "" 2
@ 89 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_vio_device_id_compat #32 offsetof(struct vio_device_id, compat)	@
@ 0 "" 2
@ 91 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_input_device_id #160 sizeof(struct input_device_id)	@
@ 0 "" 2
@ 92 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_flags #0 offsetof(struct input_device_id, flags)	@
@ 0 "" 2
@ 93 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_bustype #4 offsetof(struct input_device_id, bustype)	@
@ 0 "" 2
@ 94 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_vendor #6 offsetof(struct input_device_id, vendor)	@
@ 0 "" 2
@ 95 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_product #8 offsetof(struct input_device_id, product)	@
@ 0 "" 2
@ 96 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_version #10 offsetof(struct input_device_id, version)	@
@ 0 "" 2
@ 97 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_evbit #12 offsetof(struct input_device_id, evbit)	@
@ 0 "" 2
@ 98 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_keybit #16 offsetof(struct input_device_id, keybit)	@
@ 0 "" 2
@ 99 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_relbit #112 offsetof(struct input_device_id, relbit)	@
@ 0 "" 2
@ 100 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_absbit #116 offsetof(struct input_device_id, absbit)	@
@ 0 "" 2
@ 101 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_mscbit #124 offsetof(struct input_device_id, mscbit)	@
@ 0 "" 2
@ 102 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_ledbit #128 offsetof(struct input_device_id, ledbit)	@
@ 0 "" 2
@ 103 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_sndbit #132 offsetof(struct input_device_id, sndbit)	@
@ 0 "" 2
@ 104 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_ffbit #136 offsetof(struct input_device_id, ffbit)	@
@ 0 "" 2
@ 105 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_input_device_id_swbit #152 offsetof(struct input_device_id, swbit)	@
@ 0 "" 2
@ 107 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_eisa_device_id #12 sizeof(struct eisa_device_id)	@
@ 0 "" 2
@ 108 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_eisa_device_id_sig #0 offsetof(struct eisa_device_id, sig)	@
@ 0 "" 2
@ 110 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_parisc_device_id #8 sizeof(struct parisc_device_id)	@
@ 0 "" 2
@ 111 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_parisc_device_id_hw_type #0 offsetof(struct parisc_device_id, hw_type)	@
@ 0 "" 2
@ 112 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_parisc_device_id_hversion #2 offsetof(struct parisc_device_id, hversion)	@
@ 0 "" 2
@ 113 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_parisc_device_id_hversion_rev #1 offsetof(struct parisc_device_id, hversion_rev)	@
@ 0 "" 2
@ 114 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_parisc_device_id_sversion #4 offsetof(struct parisc_device_id, sversion)	@
@ 0 "" 2
@ 116 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_sdio_device_id #12 sizeof(struct sdio_device_id)	@
@ 0 "" 2
@ 117 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_sdio_device_id_class #0 offsetof(struct sdio_device_id, class)	@
@ 0 "" 2
@ 118 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_sdio_device_id_vendor #2 offsetof(struct sdio_device_id, vendor)	@
@ 0 "" 2
@ 119 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_sdio_device_id_device #4 offsetof(struct sdio_device_id, device)	@
@ 0 "" 2
@ 121 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_ssb_device_id #6 sizeof(struct ssb_device_id)	@
@ 0 "" 2
@ 122 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ssb_device_id_vendor #0 offsetof(struct ssb_device_id, vendor)	@
@ 0 "" 2
@ 123 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ssb_device_id_coreid #2 offsetof(struct ssb_device_id, coreid)	@
@ 0 "" 2
@ 124 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ssb_device_id_revision #4 offsetof(struct ssb_device_id, revision)	@
@ 0 "" 2
@ 126 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_bcma_device_id #6 sizeof(struct bcma_device_id)	@
@ 0 "" 2
@ 127 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_bcma_device_id_manuf #0 offsetof(struct bcma_device_id, manuf)	@
@ 0 "" 2
@ 128 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_bcma_device_id_id #2 offsetof(struct bcma_device_id, id)	@
@ 0 "" 2
@ 129 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_bcma_device_id_rev #4 offsetof(struct bcma_device_id, rev)	@
@ 0 "" 2
@ 130 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_bcma_device_id_class #5 offsetof(struct bcma_device_id, class)	@
@ 0 "" 2
@ 132 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_virtio_device_id #8 sizeof(struct virtio_device_id)	@
@ 0 "" 2
@ 133 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_virtio_device_id_device #0 offsetof(struct virtio_device_id, device)	@
@ 0 "" 2
@ 134 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_virtio_device_id_vendor #4 offsetof(struct virtio_device_id, vendor)	@
@ 0 "" 2
@ 136 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_hv_vmbus_device_id #20 sizeof(struct hv_vmbus_device_id)	@
@ 0 "" 2
@ 137 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_hv_vmbus_device_id_guid #0 offsetof(struct hv_vmbus_device_id, guid)	@
@ 0 "" 2
@ 139 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_i2c_device_id #24 sizeof(struct i2c_device_id)	@
@ 0 "" 2
@ 140 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_i2c_device_id_name #0 offsetof(struct i2c_device_id, name)	@
@ 0 "" 2
@ 142 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_spi_device_id #36 sizeof(struct spi_device_id)	@
@ 0 "" 2
@ 143 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_spi_device_id_name #0 offsetof(struct spi_device_id, name)	@
@ 0 "" 2
@ 145 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_dmi_system_id #332 sizeof(struct dmi_system_id)	@
@ 0 "" 2
@ 146 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_dmi_system_id_matches #8 offsetof(struct dmi_system_id, matches)	@
@ 0 "" 2
@ 148 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_platform_device_id #24 sizeof(struct platform_device_id)	@
@ 0 "" 2
@ 149 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_platform_device_id_name #0 offsetof(struct platform_device_id, name)	@
@ 0 "" 2
@ 151 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_mdio_device_id #8 sizeof(struct mdio_device_id)	@
@ 0 "" 2
@ 152 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_mdio_device_id_phy_id #0 offsetof(struct mdio_device_id, phy_id)	@
@ 0 "" 2
@ 153 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_mdio_device_id_phy_id_mask #4 offsetof(struct mdio_device_id, phy_id_mask)	@
@ 0 "" 2
@ 155 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_zorro_device_id #8 sizeof(struct zorro_device_id)	@
@ 0 "" 2
@ 156 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_zorro_device_id_id #0 offsetof(struct zorro_device_id, id)	@
@ 0 "" 2
@ 158 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_isapnp_device_id #12 sizeof(struct isapnp_device_id)	@
@ 0 "" 2
@ 159 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_isapnp_device_id_vendor #4 offsetof(struct isapnp_device_id, vendor)	@
@ 0 "" 2
@ 160 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_isapnp_device_id_function #6 offsetof(struct isapnp_device_id, function)	@
@ 0 "" 2
@ 162 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_ipack_device_id #12 sizeof(struct ipack_device_id)	@
@ 0 "" 2
@ 163 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ipack_device_id_format #0 offsetof(struct ipack_device_id, format)	@
@ 0 "" 2
@ 164 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ipack_device_id_vendor #4 offsetof(struct ipack_device_id, vendor)	@
@ 0 "" 2
@ 165 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_ipack_device_id_device #8 offsetof(struct ipack_device_id, device)	@
@ 0 "" 2
@ 167 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_amba_id #12 sizeof(struct amba_id)	@
@ 0 "" 2
@ 168 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_amba_id_id #0 offsetof(struct amba_id, id)	@
@ 0 "" 2
@ 169 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_amba_id_mask #4 offsetof(struct amba_id, mask)	@
@ 0 "" 2
@ 171 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_x86_cpu_id #12 sizeof(struct x86_cpu_id)	@
@ 0 "" 2
@ 172 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_x86_cpu_id_feature #6 offsetof(struct x86_cpu_id, feature)	@
@ 0 "" 2
@ 173 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_x86_cpu_id_family #2 offsetof(struct x86_cpu_id, family)	@
@ 0 "" 2
@ 174 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_x86_cpu_id_model #4 offsetof(struct x86_cpu_id, model)	@
@ 0 "" 2
@ 175 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_x86_cpu_id_vendor #0 offsetof(struct x86_cpu_id, vendor)	@
@ 0 "" 2
@ 177 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_cpu_feature #2 sizeof(struct cpu_feature)	@
@ 0 "" 2
@ 178 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_cpu_feature_feature #0 offsetof(struct cpu_feature, feature)	@
@ 0 "" 2
@ 180 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_mei_cl_device_id #36 sizeof(struct mei_cl_device_id)	@
@ 0 "" 2
@ 181 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_mei_cl_device_id_name #0 offsetof(struct mei_cl_device_id, name)	@
@ 0 "" 2
@ 183 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->SIZE_rio_device_id #8 sizeof(struct rio_device_id)	@
@ 0 "" 2
@ 184 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_rio_device_id_did #0 offsetof(struct rio_device_id, did)	@
@ 0 "" 2
@ 185 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_rio_device_id_vid #2 offsetof(struct rio_device_id, vid)	@
@ 0 "" 2
@ 186 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_rio_device_id_asm_did #4 offsetof(struct rio_device_id, asm_did)	@
@ 0 "" 2
@ 187 "/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/scripts/mod/devicetable-offsets.c" 1
	
->OFF_rio_device_id_asm_vid #6 offsetof(struct rio_device_id, asm_vid)	@
@ 0 "" 2
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	main, .-main
	.ident	"GCC: (gcc-4.9.2 + glibc-2.22 (Build by czyong) Wed Mar  9 16:30:48 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
