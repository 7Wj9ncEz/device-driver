obj-m := char_driver.o char_driver_virus.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *~i prog

test:
	gcc -o prog -W -Wall -pedantic -ansi writing_in_device.c

