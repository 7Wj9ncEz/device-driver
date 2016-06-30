obj-m := char_driver.o char_driver_virus.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *~i test virus antidote

test:
	gcc -o test -W -Wall -pedantic -ansi writing_in_device.c
	sudo chmod 777 test

virus:
	gcc -o virus -W -Wall -pedantic -ansi virus.c
	sudo chmod 777 virus

antidote:
	gcc -o antidote -W -Wall -pedantic -ansi antidote.c
	sudo chmod 777 antidote
