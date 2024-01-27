#!/bin/bash

cd linux* 2>~/../../dev/null

if [ "$?" -ne 0 ]
then
	echo "kernel: directory does not exist and will be downloaded"
	wget . https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.4.6.tar.xz
	tar -xvf linux*.tar*
	rm *.tar*
	cd linux*
fi

make defconfig
make -j$1 

if [ "$?" -ne 0 ]
then
	echo 'something went wrong'
	exit
fi

cp arch/x86_64/boot/bzImage ../../../kernel
