#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

user_name="${USER:-dev}"
user_id="$(id -u)"
group_id="$(id -g)"
image="${IMAGE:-hfi-spike-dev:${user_id}-${group_id}}"
container_riscv="${RISCV:-/workspace/hfi-build/riscv-tools}"
docker_tty=()
docker_env=(
  -e "RISCV=$container_riscv"
  -e "PATH=$container_riscv/bin:/opt/riscv/bin:/opt/riscv/riscv64-linux-gnu/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
)

if [[ -t 0 && -t 1 ]]; then
  docker_tty=(-it)
fi

for name in CLEAN CONFIGURE SPIKE_SRC_DIR SPIKE_BUILD_DIR JOBS PK SPIKE_ISA OUT_DIR CROSS_COMPILE; do
  if [[ -v "$name" ]]; then
    docker_env+=(-e "$name=${!name}")
  fi
done

docker build \
  -f "$repo_root/Dockerfile" \
  --build-arg "USER_NAME=$user_name" \
  --build-arg "USER_ID=$user_id" \
  --build-arg "GROUP_ID=$group_id" \
  -t "$image" \
  "$repo_root"

docker run --rm \
  "${docker_tty[@]}" \
  -v "$repo_root:/workspace:z" \
  -w /workspace \
  "${docker_env[@]}" \
  "$image" \
  "$@"
