cmd_kernel/rcu/built-in.o :=  arm-histbv310-linux-ld -EL    -r -o kernel/rcu/built-in.o kernel/rcu/update.o kernel/rcu/srcu.o kernel/rcu/tree.o 
