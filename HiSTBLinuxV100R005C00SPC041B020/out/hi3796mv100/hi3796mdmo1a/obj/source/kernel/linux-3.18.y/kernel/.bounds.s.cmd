cmd_kernel/bounds.s := arm-histbv310-linux-gcc -Wp,-MD,kernel/.bounds.s.d  -nostdinc -isystem /home/qgb/github/hi3798mv100/HiSTBLinuxV100R005C00SPC041B020/tools/linux/toolchains/arm-histbv310-linux/bin/../lib/gcc/arm-gcc49-linux-gnueabi/4.9.2/include -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include -Iarch/arm/include/generated  -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include -Iinclude -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi -Iinclude/generated/uapi -include /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/kconfig.h  -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/. -I. -D__KERNEL__ -mlittle-endian   -I/home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/mach-hi3798mx/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fno-ipa-sra -mabi=aapcs-linux -mno-thumb-interwork -mfpu=vfp -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -O2 --param=allow-store-data-races=0 -Wframe-larger-than=1024 -fstack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(bounds)"  -D"KBUILD_MODNAME=KBUILD_STR(bounds)"  -fverbose-asm -S -o kernel/bounds.s /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/kernel/bounds.c

source_kernel/bounds.s := /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/kernel/bounds.c

deps_kernel/bounds.s := \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/nr/cpus.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/swap.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
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
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi/asm/posix_types.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/asm-generic/posix_types.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/linkage.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/stringify.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/linkage.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/cpu/endian/be32.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/swab.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/linux/swab.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/swab.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi/asm/swab.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/qgb/github/hi3798mv100/HiSTBLinuxV100R005C00SPC041B020/tools/linux/toolchains/arm-histbv310-linux/lib/gcc/arm-gcc49-linux-gnueabi/4.9.2/include/stdarg.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/bitops.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/bitops.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/typecheck.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/irqflags.h \
    $(wildcard include/config/cpu/v7m.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi/asm/ptrace.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/hwcap.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi/asm/hwcap.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/non-atomic.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/fls64.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/sched.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/hweight.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/arch_hweight.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/const_hweight.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/lock.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/le.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/uapi/asm/byteorder.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/byteorder/little_endian.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/linux/byteorder/little_endian.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/byteorder/generic.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/printk.h \
    $(wildcard include/config/message/loglevel/default.h) \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/lto.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/kern_levels.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/linux/kernel.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/uapi/linux/sysinfo.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/dynamic_debug.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/div64.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/compiler.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/cma.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/cma/advance/share.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/kbuild.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/spinlock_types.h \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/arch/arm/include/asm/spinlock_types.h \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  /home/qgb/github/hi3796mv100/HiSTBLinuxV100R005C00SPC041B020/source/kernel/linux-3.18.y/include/linux/rwlock_types.h \

kernel/bounds.s: $(deps_kernel/bounds.s)

$(deps_kernel/bounds.s):
