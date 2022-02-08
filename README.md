# NiceArrays

The most important data structure in scientific computing is the (multidimensional) array.
C is not the friendliest language for multidimensional arrays as is.
This is my attempt to make a friendlier API type thing for multidimensional (1, 2, and 3 dimensional) arrays in C
that includes functions to mimic some of NumPy's "vectorized" features like adding a scalar to an entire matrix, 
multiplying matrices, adding a vector to a matrix, etc.
I realize that there are great libraries for C++ that do this, like Armadillo, Eigen, and Xarray, but sometimes
good old C is what one wants to use, for example if one wants to write libraries for Python to speed up inner loops.

The data structures here are really just linear heap arrays under the hood, which all the performance that entails.
These functions don't really add much overhead. A good compiler will probably inline a lot of these functions anyway.

