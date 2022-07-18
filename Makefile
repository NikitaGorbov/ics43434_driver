obj-m := ics43434.o

all:
	make -C ../linux-tn-imx/ M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
