# SPDX-License-Identifier: GPL-2.0-only
# builds the kprobes example kernel modules;
# then to use one (as root):  insmod <module_name.ko>

#obj-$(CONFIG_SAMPLE_KPROBES) += kprobe_example.o

ifeq ($(KERNELRELEASE),)

	# Assume the source tree is where the running kernel was built
	# You should set KERNELDIR in the environment if it's elsewhere
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build

	# The current directory is passed to sub-makes as argument
	PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions

.PHONY: modules modules_install clean

else
	# called from kernel build system: just declare what our modules are
	#obj-m := kprobe_example.o  
	obj-m := pfhprobe.o
endif