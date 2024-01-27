obj-m += hello.o
 
all:
	make -C ../../../kernel/linux* M=$(PWD) modules
	
clean:
	make -C ../../../kernel/linux* M=$(PWD) clean
