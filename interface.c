#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "NiceArrays.h"


// Mat* pullMat(Arr3* arr, char dir[50]); // dir e.g. "0:2,3:5" means [0:2, 3:5] not inclusive
// void pushMat(Mat* arr, Arr3* arr2, char dir[50]); // dir e.g. ":1:" means [:, 1, :]
// void pushVecToArr3(Vec* arr, Arr3* arr2, char dir[50]); // dir e.g. ":11" means [:, 1, :]
// Vec* pullVecArr3(Arr3* arr, char dir[50]); // dir e.g. ::1 means [:, :, 1]

void pushVecMat(Vec* arr, unsigned vi, unsigned vf, Mat* arr2, unsigned ri, unsigned ci,
				unsigned rf, unsigned cf) {
	/**/
	int i;

	if (ci == cf) {
		for (i = ri; i <= rf; ++i)
			arr2->val[arr2->size[0] * i + ci] = arr->val[vi + (i - ri)];
	} else {
		for (i = ci; i <= cf; ++i)
			arr2->val[arr2->size[0] * ri + i] = arr->val[vi + (i - ci)];
	}
}

Vec* pullVecMat(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf) {
	int i;
	Vec* arr2;

	if (ci == cf) {
		arr2 = zerosVec(rf - ri + 1);
		for (i = ri; i <= rf; ++i)
			arr2->val[(i - ri)] = arr->val[arr->size[0] * i + ci];
	} else {
		arr2 = zerosVec(cf - ci + 1);
		for (i = ci; i <= cf; ++i)
			arr2->val[(i - ci)] = arr->val[arr->size[0] * ri + i];
	}

	return arr2;
}

void pushMatMat(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
				Mat* arr2, unsigned ri2, unsigned ci2, unsigned rf2, unsigned cf2) {

	unsigned rows = rf - ri + 1;
	unsigned cols = cf - ci + 1;

	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			arr2->val[rows * (i + ri2) + (j + ci2)] = arr->val[rows * (i + ri) + (j + ci)];
		}
	}
}

Mat* pullMatMat(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf) {
	unsigned rows = rf - ri + 1;
	unsigned cols = cf - ci + 1;

	Mat* arr2 = zerosMat(rows, cols);

	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			arr2->val[rows * i + j] = arr->val[rows * (i + ri) + (j + ci)];
		}
	}
	return arr2;
}


void pushVecMat_safe(Vec* arr, unsigned vi, unsigned vf, Mat* arr2, unsigned ri, unsigned ci,
				unsigned rf, unsigned cf) {

	assert("matrix indices out of bounds" &&
		ri < arr2->size[0] && rf < arr2->size[0] &&
		ci < arr2->size[1] && cf < arr2->size[1]);

	assert("can't insert diagonally or x/y spans are both 0" && ri == rf ^ ci == cf);

	if (ci == cf) {
		assert("vector/matrix dimensions don't line up" &&
			(vf - vi) == (rf - ri) && (vf - vi) > 0);
	} else {
		assert("vector/matrix dimensions don't line up" &&
			(vf - vi) == (cf - ci) && (vf - vi) > 0);
	}
	pushVecMat(arr, vi, vf, arr2, ri, ci, rf, cf);
}

Vec* pullVecMat_safe(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf) {

	assert("matrix indices out of bounds" &&
		ri < arr->size[0] && rf < arr->size[0] &&
		ci < arr->size[1] && cf < arr->size[1]);

	return pullVecMat(arr, ri, ci, rf, cf);
}


