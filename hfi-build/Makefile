.PHONY: build build-tests spike spike-clean test-henter test-wasm2c test-hello test-sepstack
.DEFAULT_GOAL := build

PARALLEL_COUNT=16
EXAMPLE_FLAGS=-O0 -g
PK := $(HOME)/riscv-tools/riscv64-linux-gnu/bin/pk

RUN_SPIKE=spike --isa=rv64gc_zihfi $(PK)

spike-clean:
		cd ~/codes/spike-proj/riscv-isa-sim/build && make clean && ~/codes/spike-proj/riscv-isa-sim/configure --prefix=$(RISCV)

spike:
		cd ~/codes/spike-proj/riscv-isa-sim/build && make -j4 && sudo make install

mybuildout/test-henter: ../tests/test-henter.cpp ../tests/hfi.S
		riscv64-linux-gnu-g++ $^ $(EXAMPLE_FLAGS) -static -o $@

mybuildout/test-hello: ../tests/hello.c
		riscv64-linux-gnu-gcc $^ $(EXAMPLE_FLAGS) -static -o $@

build-tests: mybuildout/test-henter mybuildout/test-hello

test-henter: build-tests
		cd .. && $(RUN_SPIKE) mybuild/mybuildout/test-henter

test-wasm2c:
		cd .. && $(RUN_SPIKE) tests/wasm2c-test/hfi-test/riscv_test

test-hello: build-tests
		cd .. && $(RUN_SPIKE) mybuild/mybuildout/test-hello

test-sepstack:
		cd .. && $(RUN_SPIKE) tests/SepStack-test/build/sepstack-riscv-test
