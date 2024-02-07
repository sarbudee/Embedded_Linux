

obj-m = Hello_world.o

FILEPATH=/lib/modules/$(shell uname -r)/build
#KDIR = /home/sarbudeen/buildroot-2022.02.1/output/build/linux-custom
all:
	make -C $(FILEPATH) M=$(PWD) modules

clean:
	make -C $(FILEPATH) M=$(PWD) clean
