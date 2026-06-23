# Docker Development

Use the Docker wrapper when you want the Spike/HFI build dependencies without
installing them on the host:

```sh
./docker-run.sh
```

The wrapper builds `hfi-spike-dev:<uid>-<gid>` using your current UID/GID, then
bind-mounts this repository at `/workspace`. Files created in the container are
therefore owned by your host user and can be committed normally.

Common commands:

```sh
./docker-run.sh make -C hfi-build build-tests
CONFIGURE=1 ./docker-run.sh ./hfi-build/rebuild.sh
./docker-run.sh make -C hfi-build test-hello
```

The image includes Spike build dependencies, `riscv64-linux-gnu-*` cross tools,
and `pk` installed under `/opt/riscv`. The wrapper sets `RISCV` to
`/workspace/hfi-build/riscv-tools` by default, so installing Spike from inside
the container persists in the bind-mounted repo under an ignored directory.

>> ### Note
>>
>> The implementation and execution of the Dockerfile environment is tested in:
>>
>> - Ubuntu 24:04
>> - OpenSuse tumbleweed
