#!/bin/bash

# # rebuild
cd ~/codes/spike-proj/riscv-isa-sim/build
# make clean
# ../configure --prefix=$RISCV
make -j$(nproc)
sudo make install

# cd ~/codes/spike-proj/riscv-isa-sim
# riscv64-linux-gnu-gcc -static -o hello hello.c
# riscv64-linux-gnu-g++ -static -o test-henter test-henter.cpp hfi.S
# spike $HOME/riscv-tools/riscv64-linux-gnu/bin/pk test-henter
