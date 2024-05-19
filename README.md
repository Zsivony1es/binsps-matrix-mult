# Bachelor Thesis Project - Peter Ivony

The aim of this project is to explore different algorithms to multiply sparse binary matrices with real valued vectors and compare them by runtime.

## How to use
The implementation of the algorithms are done in C++ and I build the binaries using Makefile. If you are using
MacOS and have Google Test and OpenBLAS installed with Homebrew, then you most likely will not have to change anything.
Otherwise you will have to specify the path to the Google Test and OpenBLAS library installation in the Makefile. You 
can do this by changing the following variables:
```
GTEST_DIR := /path/to/gtest
BLAS_DIR := /path/to/openblas
```