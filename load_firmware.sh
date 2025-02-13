# This script is to load the firmware in the CPU which is already loaded in the FPGA

./litex/litex/tools/litex_term.py /dev/ttyUSB1 --kernel firmware/ddrapp.bin

# Now you have to press enter
# And type "reboot" to finalize the configuration