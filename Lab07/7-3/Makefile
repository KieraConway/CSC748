
MODULE_NAME = lab7-3

PWD = $(shell pwd)
KERNEL = $(shell uname -r)
KERNEL_DIR = /usr/lib/modules/$(KERNEL)/build

CFLAGS_$(MODULE_NAME).o = -Wno-unused-result

obj-m := $(MODULE_NAME).o

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
