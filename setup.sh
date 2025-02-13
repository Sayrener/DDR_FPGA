# This script is to setup the environment

# Install Migen/LiteX and the LiteX's cores

wget https://raw.githubusercontent.com/enjoy-digital/litex/master/litex_setup.py
chmod +x litex_setup.py
./litex_setup.py --init --install --user --config=standard

# Install a RISC-V toolchain

pip3 install meson ninja
sudo ./litex_setup.py --gcc=riscv

# Creating the repository for the build

mkdir build

# Now you go in the litex-boards/litex_boards/platforms/digilent_nexys4ddr.py file and modify the name of the board
# Here it is xc7a50ticsg324-1L
# And replace the 
# def create_programmer(self):
#         return OpenOCD("openocd_xc7_ft2232.cfg", "bscan_spi_xc7a100t.bit")
# by
# def create_programmer(self):
#         return VivadoProgrammer()