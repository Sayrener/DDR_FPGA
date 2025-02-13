# This script is to build the CPU

./digilent_nexys4ddr_target.py --build --output-dir ./build --sys-clk-freq 100000000 --cpu-type picorv32 --cpu-variant standard --integrated-rom-size 32768 --integrated-sram-size 131072 --with-video-framebuffer --doc
