.PHONY: build build-tests spike spike-clean test-henter test-wasm2c test-hello test-sepstack
.DEFAULT_GOAL := build

BUILD_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
ROOT_DIR := $(abspath $(BUILD_DIR)/..)
OUT_DIR ?= $(BUILD_DIR)/mybuildout

JOBS ?= $(shell nproc 2>/dev/null || echo 4)
EXAMPLE_FLAGS ?= -O0 -g
CROSS_COMPILE ?= riscv64-linux-gnu-
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++

SPIKE ?= spike
SPIKE_ISA ?= rv64gc_xhfi
SPIKE_SRC_DIR ?= $(ROOT_DIR)
SPIKE_BUILD_DIR ?= $(SPIKE_SRC_DIR)/build
SUDO ?= sudo
PK ?= $(shell if [ -x /opt/riscv/riscv64-linux-gnu/bin/pk ]; then echo /opt/riscv/riscv64-linux-gnu/bin/pk; else echo $(HOME)/riscv-tools/riscv64-linux-gnu/bin/pk; fi)

RUN_SPIKE = $(SPIKE) --isa=$(SPIKE_ISA) $(PK)

build: build-tests

$(SPIKE_BUILD_DIR):
		mkdir -p $@

spike-clean: | $(SPIKE_BUILD_DIR)
		$(MAKE) -C $(SPIKE_BUILD_DIR) clean
		cd $(SPIKE_BUILD_DIR) && $(SPIKE_SRC_DIR)/configure --prefix=$(RISCV)

spike: | $(SPIKE_BUILD_DIR)
		$(MAKE) -C $(SPIKE_BUILD_DIR) -j$(JOBS)
		$(SUDO) $(MAKE) -C $(SPIKE_BUILD_DIR) install

$(OUT_DIR):
		mkdir -p $@

$(OUT_DIR)/test-henter: $(ROOT_DIR)/tests/test-henter.cpp $(ROOT_DIR)/tests/hfi.S | $(OUT_DIR)
		$(CXX) $^ $(EXAMPLE_FLAGS) -static -o $@

$(OUT_DIR)/test-hello: $(ROOT_DIR)/tests/hello.c | $(OUT_DIR)
		$(CC) $^ $(EXAMPLE_FLAGS) -static -o $@

build-tests: $(OUT_DIR)/test-henter $(OUT_DIR)/test-hello

test-henter: build-tests
		cd $(ROOT_DIR) && $(RUN_SPIKE) $(OUT_DIR)/test-henter

test-wasm2c:
		cd $(ROOT_DIR) && $(RUN_SPIKE) $(ROOT_DIR)/tests/wasm2c-test/hfi-test/riscv_test

test-hello: build-tests
		cd $(ROOT_DIR) && $(RUN_SPIKE) $(OUT_DIR)/test-hello

test-sepstack:
		cd $(ROOT_DIR) && $(RUN_SPIKE) $(ROOT_DIR)/tests/SepStack-test/build/sepstack-riscv-test
