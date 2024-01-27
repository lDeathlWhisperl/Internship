#!/bin/bash

LINUX_DIR=$(pwd)

cd build/kernel
./build_kernel.sh $1

cd $LINUX_DIR

cd build/initrd/
./build_initrd.sh
