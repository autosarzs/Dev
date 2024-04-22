FROM ubuntu:22.04

# Avoid stuck at console asking for input
ARG DEBIAN_FRONTEND=noninteractive

# Install compiler and other tools
RUN apt-get update && \
    apt-get install -y \
    make \
    cmake \
    lsb-release \
    git \
    file \
    aptitude \
    gcc-multilib \
    python3 \
    python3-pip \
    wget \
    xz-utils \
    && rm -rf /var/lib/apt/lists/* \
    && pip3 install junit2html

# Download Linaro GCC compiler
RUN wget -c https://releases.linaro.org/components/toolchain/binaries/7.2-2017.11/arm-eabi/gcc-linaro-7.2.1-2017.11-x86_64_arm-eabi.tar.xz --no-check-certificate

# Extract Linaro GCC compiler into a folder inside /opt/compilers
RUN mkdir -p /opt/compilers/gcc-linaro-7.2.1-2017.11-x86_64_arm-eabi && \
    tar xf gcc-linaro-7.2.1-2017.11-x86_64_arm-eabi.tar.xz -C /opt/compilers/gcc-linaro-7.2.1-2017.11-x86_64_arm-eabi --strip-components=1 && \
    rm gcc-linaro-7.2.1-2017.11-x86_64_arm-eabi.tar.xz

# Set the default command
CMD ["/bin/bash"]
