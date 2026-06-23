FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive
ARG USER_NAME=dev
ARG USER_ID=1000
ARG GROUP_ID=1000
ARG RISCV_PK_REF=master

ENV RISCV=/opt/riscv
ENV PATH=/opt/riscv/bin:/opt/riscv/riscv64-linux-gnu/bin:$PATH

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
    autoconf \
    automake \
    autotools-dev \
    bash \
    binutils-riscv64-linux-gnu \
    build-essential \
    ca-certificates \
    device-tree-compiler \
    g++-riscv64-linux-gnu \
    gcc-riscv64-linux-gnu \
    gdb-multiarch \
    git \
    libc6-dev-riscv64-cross \
    libboost-regex-dev \
    libboost-system-dev \
    libtool \
    make \
    pkg-config \
    sudo \
    vim \
    less \
 && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 https://github.com/riscv-software-src/riscv-pk.git /tmp/riscv-pk \
 && cd /tmp/riscv-pk \
 && if [ "$RISCV_PK_REF" != "master" ]; then \
      git fetch --depth 1 origin "$RISCV_PK_REF" && git checkout FETCH_HEAD; \
    fi \
 && mkdir build \
 && cd build \
 && ../configure --prefix="$RISCV" --host=riscv64-linux-gnu \
 && make -j"$(nproc)" \
 && make install \
 && rm -rf /tmp/riscv-pk

RUN set -eux; \
    if ! getent group "$GROUP_ID" >/dev/null; then \
      groupadd --gid "$GROUP_ID" "$USER_NAME"; \
    fi; \
    existing_user="$(getent passwd "$USER_ID" | cut -d: -f1 || true)"; \
    if [ -n "$existing_user" ]; then \
      if [ "$existing_user" != "$USER_NAME" ]; then \
        usermod --login "$USER_NAME" "$existing_user"; \
      fi; \
      usermod --gid "$GROUP_ID" --home /home/"$USER_NAME" --move-home --shell /bin/bash "$USER_NAME"; \
    else \
      useradd --uid "$USER_ID" --gid "$GROUP_ID" --create-home --shell /bin/bash "$USER_NAME"; \
    fi; \
    echo "$USER_NAME ALL=(ALL) NOPASSWD:ALL" >/etc/sudoers.d/"$USER_NAME"; \
    chmod 0440 /etc/sudoers.d/"$USER_NAME"; \
    mkdir -p /workspace "$RISCV"; \
    chown -R "$USER_ID:$GROUP_ID" /workspace "$RISCV" /home/"$USER_NAME"

USER $USER_NAME
WORKDIR /workspace

CMD ["bash", "-l"]
