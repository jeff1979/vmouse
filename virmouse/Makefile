obj-m += virmouse.o

KERNELDIR ?= ../linux-source
PWD  := $(shell pwd)


KBUILD_CFLAGS   += -Wno-error=unused-result \
	           -Werror=return-type
			   
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	@rm -fr *.ko *.o
