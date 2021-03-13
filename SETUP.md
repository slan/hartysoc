# Development environment setup

## Quickstart

If you feel brave, a setup script can be found [here](setup.sh). It takes around 10 minutes to download everything and build yosys from source.

## Step-by-step

All the commands below are meant to be executed from a project folder (I'm using `~/src` but there should not be any hard references besides the path to `riscv-formal` in the `Makefile`)

From a fresh install of Ubuntu 20.04/WSL:

1. Clone hartysoc

```
git clone https://github.com/slan/artysoc.git
```

2. Install `pip` and `venv`

```
sudo apt-get update
sudo apt-get install -y python3-pip python3-venv
```

3. Create and activate python virtual environment in `~/virtualenvs/hartysoc`

```
python3 -m venv ~/virtualenvs/hartysoc
. ~/virtualenvs/hartysoc/bin/activate
```

4. Install Install nmigen and yosys from source (pypi is lagging behind)

```
git clone https://github.com/nmigen/nmigen.git
pip install -e nmigen
git clone https://github.com/nmigen/nmigen-boards.git
pip install -e nmigen-boards
```

5. Install yosys from source (note: install will be in `/usr/local`)

```
sudo apt-get install -y build-essential clang bison flex \
                libreadline-dev gawk tcl-dev libffi-dev git \
                graphviz xdot pkg-config python3 libboost-system-dev \
                libboost-python-dev libboost-filesystem-dev zlib1g-dev
git clone https://github.com/YosysHQ/yosys.git
cd yosys&&make config-clang&&make -j$(nproc)&&sudo make install&&cd ..
```

6. Install the HiFive gcc toolchain in `/usr/local`:

```
mkdir -p ~/tools&&wget -O- https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz|sudo tar -C /usr/local --strip-components=1 -xzf -
```
> STOP! you can now `make sim` to run Dhrystone

7. Install Verilog-VCD, install [riscv-formal](https://github.com/slan/riscv-formal.git) from my fork so you can run the verification out-of-tree:

```
pip install Verilog_VCD
git clone https://github.com/slan/riscv-formal.git
```

> STOP! you can now `make formal -j$(nproc)` to verify the core

8. Install vivado (manually) and make sure it's in your `${PATH}`

> STOP! you can now `make arty` to generate a bitstream

9. Install openocd in `/usr/local`:

```
wget -O- https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz|sudo tar -C /usr/local --strip-components=1 -xzf -
```

Configure serial (or use `minicom`), your device might be different...

```
sudo stty -F /dev/ttyUSB1 ispeed 115200 raw
sudo cat /dev/ttyUSB1
```

> STOP! you can now `make prog` to run Dhrystone on the FPGA
