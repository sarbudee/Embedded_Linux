
obj-m +=Driver_1.o
obj-m +=Driver_2.o
#obj-m +=maindep.o
#obj-m +=dep.o
KDIR =/lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean


