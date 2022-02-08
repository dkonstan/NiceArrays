#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <mkl.h>
#include "NiceArrays.h"


// void eig(Mat *);
// void eigval(Mat *);

void aM(Mat* mat, unsigned row, unsigned col, double val) {
	mat->val[mat->size[0] * row + col] = val;
}
Mat* makeMat(unsigned rows, unsigned cols, double *data) {

	Mat* mat;
	mat = (Mat*) malloc(sizeof(Mat));
	if (data == NULL) {
		mat->val = (double *) calloc(rows * cols, sizeof(double));
	} else {
		mat->val = data;
	}

	mat->size[0] = rows;
	mat->size[1] = cols;

	return mat;
}
double el2(Mat* mat, unsigned i, unsigned j) {
	return mat->val[mat->size[0] * i + j];
}
Mat* copyMat(Mat* arr) {
	Mat *arr2 = zerosMat(arr->size[0], arr->size[1]);
	memcpy(arr2->val, arr->val, sizeof(double) * arr->size[0] * arr->size[1]);
	return arr2;
}
Mat* addMat(Mat* arr, double num) {
	for (int i = 0; i < arr->size[0] * arr->size[1]; ++i) {
		arr->val[i] += num;
	}
	return arr;
}
Mat* subMat(Mat* arr, double num) {
	for (int i = 0; i < arr->size[0] * arr->size[1]; ++i) {
		arr->val[i] -= num;
	}
	return arr;
}
Mat* mulMat(Mat* arr, double num) {
	for (int i = 0; i < arr->size[0] * arr->size[1]; ++i) {
		arr->val[i] *= num;
	}
	return arr;
}
Mat* divMat(Mat* arr, double num) {
	for (int i = 0; i < arr->size[0] * arr->size[1]; ++i) {
		arr->val[i] /= num;
	}
	return arr;
}
Mat* addMats(Mat* arr, Mat* arr2) {
	for (int i = 0; i < arr->size[0] * arr->size[1]; ++i) {
		arr->val[i] += arr2->val[i];
	}
	return arr;
}
Mat* subMats(Mat* arr, Mat* arr2) {
	for (int i = 0; i < arr->size[0] * arr->size[1]; ++i) {
		arr->val[i] -= arr2->val[i];
	}
	return arr;
}

Mat* mulMats(Mat* arr, Mat* arr2) {
	for (int i = 0; i < arr->size[0] * arr->size[1]; ++i) {
		arr->val[i] *= arr2->val[i];
	}
	return arr;
}
Mat* divMats(Mat* arr, Mat* arr2) {
	for (int i = 0; i < arr->size[0] * arr->size[1]; ++i) {
		arr->val[i] /= arr2->val[i];
	}
	return arr;
}
void printMat(Mat* mat) {
	printf("matrix of doubles, %d by %d\n", mat->size[0], mat->size[1]);
	printf("contents:\n");
	int i, j;
	for (i = 0; i < mat->size[0]; ++i) {
		printf("[ ");
		for (j = 0; j < mat->size[1]; ++j) {
			printf("%0.3g ", mat->val[i * mat->size[0] + j]);
		}
		printf("]\n");
	}
}
void deleteMat(Mat* mat) {
	free(mat->val); mat->val = NULL;
	free(mat); mat = NULL;
}
Mat* matmul(Mat* A, Mat* B) {

	double alpha = 1.0, beta = 0.0;
	unsigned m = A->size[0], k = A->size[1], n = B->size[1];

	Mat* C = zerosMat(m, n);

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
				m, n, k, alpha, A->val, k, B->val, n, beta, C->val, n);

	return C;
}
void eigSymm(Mat* A, Mat* eigVecs, Vec* eigVals) {

	lapack_int info, n, il, iu;
	double vl, vu, abstol;
	lapack_int* isuppz;
	/* il iu il vu unused if calculating all vecs and vals */

	n = A->size[0];
	abstol = -1;
	isuppz = (lapack_int*) malloc(sizeof(lapack_int) * 2 * n);

	info = LAPACKE_dsyevr(LAPACK_ROW_MAJOR, 'V', 'A', 'U',
		n, A->val, n, vl, vu, il, iu, abstol, &n,
		eigVals->val, eigVecs->val, n, isuppz);

	free(isuppz);

	if (info != 0) {
		puts("diagonalization failed");
		exit(EXIT_FAILURE);
	}
}

/* bounds-checked (slower) alternatives */
Mat* addMats_safe(Mat* arr, Mat* arr2) {
	assert("getAddMats: matrices have unequal dimensions" &&
		   arr->size[0] == arr2->size[0] && arr->size[1] == arr->size[1]);
	return addMats(arr, arr2);
}
Mat* subMats_safe(Mat* arr, Mat* arr2) {
	assert("getSubMats: matrices have unequal dimensions" &&
		   arr->size[0] == arr2->size[0] && arr->size[1] == arr->size[1]);
	return subMats(arr, arr2);
}
Mat* mulMats_safe(Mat* arr, Mat* arr2) {
	assert("getMulMats: matrices have unequal dimensions" &&
		   arr->size[0] == arr2->size[0] && arr->size[1] == arr->size[1]);	
	return mulMats(arr, arr2);
}
Mat* divMats_safe(Mat* arr, Mat* arr2) {
	assert("getDivMats: matrices have unequal dimensions" &&
		   arr->size[0] == arr2->size[0] && arr->size[1] == arr->size[1]);
	return divMats(arr, arr2);
}
Mat* matmul_safe(Mat* arr, Mat* arr2) {
	assert("getMatmul: matrix dimensions are incompatible" &&
		   arr->size[1] == arr2->size[0]);
	return matmul(arr, arr2);
}
void eigSymm_safe(Mat* arr, Mat* eigVecs, Vec* eigVals) {
	assert("getEigSymm: array dimensions are wrong" &&
		   arr->size[0] == eigVecs->size[0] &&
		   arr->size[1] == eigVecs->size[1] &&
		   arr->size[0] == arr->size[1] &&
		   arr->size[0] == eigVals->size);
	eigSymm(arr, eigVecs, eigVals);
}
double el2_safe(Mat* mat, unsigned i, unsigned j) {
	assert("getEl2: matrix indices are out of bounds" &&
		   i > 0 && j > 0 &&
		   i < mat->size[0] && j < mat->size[1]);
	return el2(mat, i, j);
}

