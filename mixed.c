#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NiceArrays.h"


Mat* matAddVec(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
			   Vec* arr2, unsigned vi, unsigned vf) {

	int i;

	if (ci == cf) {
		for (i = ri; i <= rf; ++i) {
			arr->val[ri * arr->size[0] + ci] += arr2->val[vi + (i - ri)];
		}
	} else {
		for (i = ci; i <= cf; ++i) {
			arr->val[ri * arr->size[0] + ci] += arr2->val[vi + (i - ci)];
		}	
	}
	return arr;
}

Mat* matSubVec(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
			   Vec* arr2, unsigned vi, unsigned vf) {
	int i;

	if (ci == cf) {
		for (i = ri; i <= rf; ++i) {
			arr->val[ri * arr->size[0] + ci] -= arr2->val[vi + (i - ri)];
		}
	} else {
		for (i = ci; i <= cf; ++i) {
			arr->val[ri * arr->size[0] + ci] -= arr2->val[vi + (i - ci)];
		}	
	}
	return arr;
}

Mat* matMulVec(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
			   Vec* arr2, unsigned vi, unsigned vf) {

	int i;

	if (ci == cf) {
		for (i = ri; i <= rf; ++i) {
			arr->val[ri * arr->size[0] + ci] *= arr2->val[vi + (i - ri)];
		}
	} else {
		for (i = ci; i <= cf; ++i) {
			arr->val[ri * arr->size[0] + ci] *= arr2->val[vi + (i - ci)];
		}	
	}
	return arr;
}


Mat* matDivVec(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
			   Vec* arr2, unsigned vi, unsigned vf) {

	int i;

	if (ci == cf) {
		for (i = ri; i <= rf; ++i) {
			arr->val[ri * arr->size[0] + ci] /= arr2->val[vi + (i - ri)];
		}
	} else {
		for (i = ci; i <= cf; ++i) {
			arr->val[ri * arr->size[0] + ci] /= arr2->val[vi + (i - ci)];
		}	
	}
	return arr;
}

