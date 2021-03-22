#!/bin/bash

git clone https://github.com/slan/hartysoc.git

sudo -v
sudo apt-get update
sudo apt-get install -y python3 python3-pip python3-venv \
    build-essential clang bison flex \
    libreadline-dev gawk tcl-dev libffi-dev git \
    graphviz xdot pkg-config python3 libboost-system-dev \
    libboost-python-dev libboost-filesystem-dev zlib1g-dev

python3 -m venv virtualenv/hartysoc
. virtualenv/hartysoc/bin/activate

pip install --no-binary :all: Verilog_VCD

git clone https://github.com/slan/nmigen.git
pip install -e nmigen
git clone https://github.com/nmigen/nmigen-boards.git
pip install -e nmigen-boards

git clone https://github.com/YosysHQ/yosys.git
cd yosys&&make config-clang&&make -j$(nproc)&&sudo make install&&cd ..

wget -O- https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz|sudo tar -C /usr/local --strip-components=1 -xzf -

git clone https://github.com/slan/riscv-formal.git

wget -O- https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz|sudo tar -C /usr/local --strip-components=1 -xzf -
sudo cp hartysoc/platform/arty/99-openocd.rules /etc/udev/rules.d/
