#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "NiceArrays.h"


void aV(Vec* arr, unsigned idx, double val) {
	arr->val[idx] = val;
}
double normV(Vec* arr) {
	double norm = 0.0;
	for (int i = 0; i < arr->size; ++i) {
		norm += arr->val[i] * arr->val[i];
	}
	return sqrt(norm);
}
Vec* makeVec(unsigned size, double *data) {

	Vec *vec;
	vec = (Vec *) malloc(sizeof(vec));
	if (data == NULL) {
		vec->val = (double *) calloc(size, sizeof(double));
	} else {
		vec->val = data;
	}

	vec->size = size;

	return vec;
}
double el(Vec* vec, unsigned i) {
	return vec->val[i];
}
Vec* copyVec(Vec* arr) {
	Vec *arr2 = zerosVec(arr->size);
	memcpy(arr2->val, arr->val, sizeof(double) * arr->size);
	return arr2;
}
Vec* addVec(Vec* arr, double num) {
	for (int i = 0; i < arr->size; ++i) {
		arr->val[i] += num;
	}
	return arr;
}
Vec* subVec(Vec* arr, double num) {
	for (int i = 0; i < arr->size; ++i) {
		arr->val[i] -= num;
	}
	return arr;
}
Vec* mulVec(Vec* arr, double num) {
	for (int i = 0; i < arr->size; ++i) {
		arr->val[i] *= num;
	}
	return arr;
}
Vec* divVec(Vec* arr, double num) {
	for (int i = 0; i < arr->size; ++i) {
		arr->val[i] /= num;
	}
	return arr;
}
Vec* addVecs(Vec* arr, Vec* arr2) {
	for (int i = 0; i < arr->size; ++i) {
		arr->val[i] += arr2->val[i];
	}
	return arr;
}
Vec* subVecs(Vec* arr, Vec* arr2) {
	for (int i = 0; i < arr->size; ++i) {
		arr->val[i] -= arr2->val[i];
	}
	return arr;
}
Vec* mulVecs(Vec* arr, Vec* arr2) {
	for (int i = 0; i < arr->size; ++i) {
		arr->val[i] *= arr2->val[i];
	}
	return arr;
}
Vec* divVecs(Vec* arr, Vec* arr2) {
	for (int i = 0; i < arr->size; ++i) {
		arr->val[i] /= arr2->val[i];
	}
	return arr;
}
void deleteVec(Vec *vec) {
	free(vec->val); vec->val = NULL;
	free(vec); vec = NULL;
}
void printVec(Vec *vec) {
	printf("vector of %d doubles\n", vec->size);
	printf("contents:\n[ ");
	for (int i = 0; i < vec->size; ++i) {
		printf("%0.3g ", vec->val[i]);
		if (i % 8 == 0 && i != 0) printf("...\n  ");
	}
	printf("]\n");
}
double dotVecs(Vec* A, Vec* B) {
	double dot = 0.0;
	for (int i = 0; i < A->size; ++i) {
		dot += A->val[i] * B->val[i];
	}
	return dot;
}
Vec* crossVecs(Vec* A, Vec* B) {

	double* a = A->val;
	double* b = B->val;

	Vec* cross = zerosVec(3);
	cross->val[0] = a[1] * b[2] - a[2] * b[1];
	cross->val[1] = a[0] * b[2] - a[2] * b[0];
	cross->val[2] = a[0] * b[1] - a[1] * b[0];	

	return cross;
}

// these are bounds-checked versions (slower, safer)
Vec* addVecs_safe(Vec* arr, Vec* arr2) {
	assert("getAddVecs: vectors have unequal length" &&
		   arr->size == arr2->size);
	return addVecs(arr, arr2);
}
Vec* subVecs_safe(Vec* arr, Vec* arr2) {
	assert("getSubVecs: vectors have unequal length" &&
		   arr->size == arr2->size);
	return subVecs(arr, arr2);
}
Vec* mulVecs_safe(Vec* arr, Vec* arr2) {
	assert("getMulVecs: vectors have unequal length" &&
		   arr->size == arr2->size);
	return mulVecs(arr, arr2);
}
Vec* divVecs_safe(Vec* arr, Vec* arr2) {
	assert("getDivVecs: vectors have unequal length" &&
		   arr->size == arr2->size);
	return divVecs(arr, arr2);
}
double dotVecs_safe(Vec* A, Vec* B) {
	assert("getDivVecs: vectors have unequal length" &&
		   A->size == B->size);
	return dotVecs(A, B);
}
Vec* crossVecs_safe(Vec* A, Vec* B) {
	assert("crossVec: vectors must be length 3" &&
	   	   A->size == 3 && B->size == 3);
	return crossVecs(A, B);
}
double el_safe(Vec* vec, unsigned i) {
	assert("el: vector index out of bounds" &&
		   i < vec->size && i > 0);
	return el(vec, i);
}
