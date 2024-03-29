# Development environment setup

## Quickstart

If you feel brave, a setup script can be found [here](setup.sh). Run it from an empty folder (you can move it afterwards):

```
wget https://raw.githubusercontent.com/slan/hartysoc/master/setup.sh
. ./setup.sh
```

This uses `sudo` to update `udev` rules and install yosys, openocd and the riscv toolchain in `/usr/local`
It takes around 4 minutes to download everything and build yosys from source.

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

3. Create and activate python virtual environment in `virtualenvs/hartysoc`

```
python3 -m venv virtualenvs/hartysoc
. virtualenvs/hartysoc/bin/activate
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
pip install --no-binary :all: Verilog_VCD
git clone -b develop https://github.com/slan/riscv-formal.git
```

8. Install symbiyosys to `/usr/local`:

```
git clone https://github.com/YosysHQ/SymbiYosys.git SymbiYosys
cd SymbiYosys
sudo make install
cd ..
```

9. Install  boolector to `/usr/local`:

```
sudo apt-get install -y cmake
git clone https://github.com/boolector/boolector
cd boolector
./contrib/setup-btor2tools.sh
./contrib/setup-lingeling.sh
./configure.sh
make -C build -j$(nproc)
sudo cp build/bin/{boolector,btor*} /usr/local/bin/
sudo cp deps/btor2tools/bin/btorsim /usr/local/bin/
cd ..
```

> STOP! you can now `make formal -j$(nproc)` to verify the core

10. Install vivado (manually) and make sure it's in your `${PATH}`

> STOP! you can now `make arty` to generate a bitstream

11. Install openocd in `/usr/local`:

```
wget -O- https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz|sudo tar -C /usr/local --strip-components=1 -xzf -
```

Add udev rules for non-root access to serial:

```
sudo cp platform/arty/99-openocd.rules /etc/udev/rules.d/
```

Configure serial (or use `minicom`), your device might be different...

```
stty -F /dev/ttyUSB1 ospeed 115200
cat /dev/ttyUSB1
```

> STOP! you can now `make prog` to run Dhrystone on the FPGA
