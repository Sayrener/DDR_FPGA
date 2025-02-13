# This script is to load the CPU on the FPGA boards

# Your Nexys A7 50T board must be connected to your computer
# To verify this see if the following command 

djtgcfg enum

# gives you something like this

# Found 1 device(s)

# Device: NexysA7
#     Device Transport Type: 00020001 (USB)
#     Product Name:          Digilent Nexys A7 -50T
#     User Name:             NexysA7
#     Serial Number:         210292B5787E

./digilent_nexys4ddr_target.py --load --output-dir ./build
