#!/bin/bash

cd fs/modules
make clean
make
cd ../..

cd busybox* 2>~/../../dev/null

if [ "$?" -ne 0 ]
then
	echo "initrd: directory does not exist and will be downloaded"
	wget . https://busybox.net/downloads/busybox-1.36.1.tar.bz2
	tar -xjvf busybox*.tar*
	rm *.tar*
	cd busybox*
fi

mkdir ../fs/bin ../fs/dev ../fs/proc ../fs/sys 2>~/../../dev/null

make defconfig
make LDFLAGS=-static
cp busybox ../fs/bin
cd ../fs/bin

for prog in $(./busybox --list)
do 
	ln -s /bin/busybox $prog
done

cd ..
find . | cpio -o -H newc > ../../../initrd.img
