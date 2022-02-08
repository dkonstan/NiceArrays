#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct Array {
	double* val;
	unsigned *dim; // "2, 3, 4, 5"
	unsigned N;
} Array; 

Array* makeArray(double* data, unsigned dim[], unsigned N) {
	Array* arr;
	arr = (Array *) malloc(sizeof(Array));
	arr->val = data;
	arr->dim = dim;
	return arr;
}


int main() {
67, 3)

	return 0;
}

