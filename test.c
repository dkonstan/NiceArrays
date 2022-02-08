#include "NiceArrays.h"


int main() {

	Vec* x = zerosVec(3);
	Vec* y = zerosVec(3);
	Mat* mat = zerosMat(3, 4);
	aM(mat, 1, 2, 2.71828);

	x = addVec(x, 1);
	y = addVec(y, 1);

	aV(x, 0, 3.14);
	aV(y, 0, 3.4);
	aV(y, 1, -3.4);
	// el_safe(y, 3);
	Vec* z = crossVecs(x, y);
	// double norm = normV(z);
	// printf("%f\n", norm);
	z = divVec(z, normV(z));

	printVec(x);
	printVec(y);
	printVec(z);
	printMat(mat);

	deleteVec(x);
	deleteVec(y);
	deleteVec(z);
	deleteMat(mat);

	return 0;
}