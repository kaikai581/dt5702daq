PYBIND11_INC=$(shell python3 -m pybind11 --includes)
LIB_EXT=$(shell python3-config --extension-suffix)
all:
	c++ -O3 -Wall -shared -std=c++11 -fPIC $(PYBIND11_INC) binder.cc FEBDTP.cxx -o FEBDTP$(LIB_EXT)