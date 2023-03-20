#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and synthesizes the digitrec program
#
# @desc: 1. "make" runs csim by default
#        2. "make csim" compiles & executes the fixed-point implementation
#        3. "make clean" cleans up the directory


# Extract Vivado HLS include path
VHLS_PATH := $(dir $(shell which vivado_hls))/..
VHLS_INC ?= ${VHLS_PATH}/include

CFLAGS = -g -I${VHLS_INC} -DHLS_NO_XIL_FPO_LIB 

all: lab4

hls: hls_second_conv.cpp
	@echo "Compiling & simulating cnn on amdpool ..."
	g++ ${CFLAGS} $^ -o bnn -lrt
	./bnn

hls_2c: hls_2c.cpp
	@echo "Compiling & simulating cnn on amdpool ..."
	g++ ${CFLAGS} $^ -o hcl_2c -lrt
	./hcl_2c

lab4: lab4_conv.cpp
	@echo "Compiling & simulating cnn on amdpool ..."
	g++ ${CFLAGS} $^ -o lab4 -lrt
	./lab4


bitstream: 
	@echo "Synthesizing cnn and creating bitstream on amdpool ..."
	vivado_hls -f run.tcl
	./run_bitstream.sh

vivado:
	@echo "Run Vivado csim and HLS"
	vivado_hls -f run.tcl

clean:
	rm -rf bnn *.dat *.prj *.log
	rm -rf zedboard_project* xillydemo.bit
