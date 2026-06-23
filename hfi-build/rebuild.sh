#!/bin/bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"

: "${SPIKE_SRC_DIR:=$repo_root}"
: "${SPIKE_BUILD_DIR:=$SPIKE_SRC_DIR/build}"
: "${JOBS:=$(nproc 2>/dev/null || echo 4)}"
: "${SUDO:=sudo}"

mkdir -p "$SPIKE_BUILD_DIR"

if [[ "${CLEAN:-0}" == "1" ]]; then
  make -C "$SPIKE_BUILD_DIR" clean
fi

if [[ "${CONFIGURE:-0}" == "1" ]]; then
  if [[ -z "${RISCV:-}" ]]; then
    echo "RISCV must be set when CONFIGURE=1" >&2
    exit 1
  fi
  (cd "$SPIKE_BUILD_DIR" && "$SPIKE_SRC_DIR/configure" --prefix="$RISCV")
fi

make -C "$SPIKE_BUILD_DIR" -j"$JOBS"
$SUDO make -C "$SPIKE_BUILD_DIR" install

# cd ~/codes/spike-proj/riscv-isa-sim
# riscv64-linux-gnu-gcc -static -o hello hello.c
# riscv64-linux-gnu-g++ -static -o test-henter test-henter.cpp hfi.S
# spike $HOME/riscv-tools/riscv64-linux-gnu/bin/pk test-henter
