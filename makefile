CC = /usr/bin/clang

HEADERS = $(wildcard *.h)
TARGET = $(patsubst %.h, lib%.so, $(HEADERS))

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

C_FLAGS = -O3 -DMKL_ILP64 -m64 $(INC_DIR) -fpic

INC_DIR = \
-I.\
-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/ \
-I/opt/intel/compilers_and_libraries_2019.4.233/mac/mkl/include/

LIB_DIR = \
-L.\
-L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib \
-L/opt/intel/compilers_and_libraries_2019.4.233/mac/mkl/lib \
-L/opt/intel/compilers_and_libraries_2019.4.233/mac/compiler/lib

# software.intel.com/en-us/articles/intel-mkl-function-finding-advisor
RUNTIME_DIR = \
-rpath,/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/libm,$\
-rpath,/opt/intel/compilers_and_libraries_2019.4.233/mac/mkl/lib,$\
-rpath,/opt/intel/compilers_and_libraries_2019.4.233/mac/compiler/lib

MKL_FLAGS = -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core \
-liomp5 -lpthread -lm -ldl

LINK_FLAGS = -Wl,$(RUNTIME_DIR), $(MKL_FLAGS)

all: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CC) $(C_FLAGS) $(LIB_DIR) $(LINK_FLAGS) -shared -o $@ $^

$(OBJ): $(HEADERS) $(SRC)
	$(CC) $(C_FLAGS) -c $(SRC)

clean:
	rm -f *.o *.gch