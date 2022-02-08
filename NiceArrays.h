#include <stdlib.h>
#include <stdio.h>
#include <mkl.h>
#include <complex.h>


#ifndef NICE_ARRAYS_H
#define NICE_ARRAYS_H

/* only routines ending in "_safe" do bounds/dimension checks
you can call these with [routineName]_safe or just [routineName]_ 
they are a bit slower, obviously */

/* --- vectors --- */
typedef struct {
	unsigned size;
	double *val;
} Vec;
void aV(Vec* arr, unsigned idx, double val);
double normV(Vec* arr);
Vec* makeVec(unsigned size, double *data);
#define zerosVec(n) (makeVec((n), NULL))
Vec* copyVec(Vec* arr);
Vec* addVec(Vec* arr, double num);
Vec* subVec(Vec* arr, double num);
Vec* mulVec(Vec* arr, double num);
Vec* divVec(Vec* arr, double num);
Vec* addVecs(Vec* arr, Vec* arr2);
Vec* subVecs(Vec* arr, Vec* arr2);
Vec* mulVecs(Vec* arr, Vec* arr2);
Vec* divVecs(Vec* arr, Vec* arr2);
Vec* crossVecs(Vec* A, Vec* B);
void deleteVec(Vec *arr);
void printVec(Vec *arr);
double dotVecs(Vec* A, Vec* B);
double el(Vec* vec, unsigned i);

/* bounds-checked, slower, alternatives */
Vec* addVecs_safe(Vec* arr, Vec* arr2);
Vec* subVecs_safe(Vec* arr, Vec* arr2);
Vec* mulVecs_safe(Vec* arr, Vec* arr2);
Vec* divVecs_safe(Vec* arr, Vec* arr2);
double dotVecs_safe(Vec* A, Vec* B);
Vec* crossVecs_safe(Vec* A, Vec* B);
double el_safe(Vec* vec, unsigned i);

#define addVecs_ addVecs_safe
#define subVecs_ subVecs_safe
#define mulVecs_ mulVecs_safe
#define divVecs_ divVecs_safe
#define dotVecs_ dotVecs_safe
#define crossVecs_ crossVecs_safe
#define el_ el_safe

/* --- matrices --- */
typedef struct {
	unsigned size[2];
	double *val;
} Mat;

void aM(Mat*, unsigned row, unsigned col, double val);
Mat* makeMat(unsigned rows, unsigned cols, double *data);
#define zerosMat(m, n) (makeMat((m), (n), NULL))
double el2(Mat* mat, unsigned i, unsigned j);
Mat* copyMat(Mat* arr);
Mat* addMat(Mat* arr, double num);
Mat* subMat(Mat* arr, double num);
Mat* mulMat(Mat* arr, double num);
Mat* divMat(Mat* arr, double num);
Mat* addMats(Mat* arr, Mat* arr2);
Mat* subMats(Mat* arr, Mat* arr2);
Mat* mulMats(Mat* arr, Mat* arr2);
Mat* divMats(Mat* arr, Mat* arr2);
void deleteMat(Mat* arr);
void printMat(Mat* arr);
Mat* matmul(Mat* arr, Mat* arr2);
void eigSymm(Mat* arr, Mat* eigVecs, Vec* eigVals);
void eig(Mat* arr);
void eigval(Mat* arr);

/* bounds-checked (slower) alternatives */
Mat* addMats_safe(Mat* arr, Mat* arr2);
Mat* subMats_safe(Mat* arr, Mat* arr2);
Mat* mulMats_safe(Mat* arr, Mat* arr2);
Mat* divMats_safe(Mat* arr, Mat* arr2);
Mat* matmul_safe(Mat* arr, Mat* arr2);
void eigSymm_safe(Mat* arr, Mat* eigVecs, Vec* eigVals);
void eig_safe(Mat* arr);
void eigval_safe(Mat* arr);
double el2_safe(Mat* arr, unsigned row, unsigned col);

#define addMats_ addMats_safe
#define subMats_ subMats_safe
#define mulMats_ mulMats_safe
#define divMats_ divMats_safe
#define matmul_ matmul_safe
#define eigSymm_ eigSymm_safe
#define eig_ eig_safe
#define eigval_ eigval_safe
#define el2_ el2_safe

/* --- 3D arrays --- */
typedef struct {
	unsigned size[3];
	double *val;
} Arr3;

Arr3* makeArr3(unsigned i, unsigned j, unsigned k, double *data);
#define zerosArr3(k, m, n) (makeArr3((k), (m), (n), NULL))
Arr3* copyArr3(Arr3* arr);
Arr3* addArr3(Arr3* arr, double num);
Arr3* subArr3(Arr3* arr, double num);
Arr3* mulArr3(Arr3* arr, double num);
Arr3* divArr3(Arr3* arr, double num);
Arr3* addArr3s(Arr3* arr, Arr3* arr2);
Arr3* subArr3s(Arr3* arr, Arr3* arr2);
Arr3* mulArr3s(Arr3* arr, Arr3* arr2);
Arr3* divArr3s(Arr3* arr, Arr3* arr2);
void deleteArr3(Arr3* arr);
void printArr3(Arr3* arr);
#define el3(arr, i, j, k) (arr->val[arr->size[0] * (arr)->size[1] * (i) + (arr)->size[1] * (j) + (k)])

/* --- interface between vectors, matrices, 3D arrays --- */
void pushVecMat(Vec* arr, unsigned vi, unsigned vf, Mat* arr2, unsigned ri, unsigned ci, unsigned rf, unsigned cf);
Vec* pullVecMat(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf);
void pushMatMat(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
				Mat* arr2, unsigned ri2, unsigned ci2, unsigned rf2, unsigned cf2);
Mat* pullMatMat(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf);

// void pushVecArr3(Vec* arr, Arr3* arr2, char dir[50]); // dir e.g. ":11" means [:, 1, :]
// Vec* pullVecArr3(Arr3* arr, char dir[50]); // dir e.g. ::1 means [:, :, 1]
// void pushMatArr3(Mat* arr, Arr3* arr2, char dir[50]); // dir e.g. ":1:" means [:, 1, :]
// Mat* pullMatArr3(Arr3* arr, char dir[50]); // dir e.g. "0:2,3:5" means [0:2, 3:5] not inclusive

void pushVecMat_safe(Vec* arr, unsigned vi, unsigned vf, Mat* arr2, unsigned ri, unsigned ci,
					 unsigned rf, unsigned cf);
Vec* pullVecMat_safe(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf);
// void pushMatMat_safe(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
// 				Mat* arr2, unsigned ri2, unsigned ci2, unsigned rf2, unsigned cf2);
// Mat* pullMatMat_safe(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf);

#define pushVecMat_ pushVecMat_safe
#define pullVecMat_ pushVecMat_safe
#define pushMatMat_ pushMatMat_safe
#define pullMatMat_ pullMatMat_safe

/* ---- mixed vector/matrix/arr3 operations --- */
Mat* matAddVec(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
			   Vec* arr2, unsigned vi, unsigned vf);
Mat* matSubVec(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
			   Vec* arr2, unsigned vi, unsigned vf);
Mat* matMulVec(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
			   Vec* arr2, unsigned vi, unsigned vf);
Mat* matDivVec(Mat* arr, unsigned ri, unsigned ci, unsigned rf, unsigned cf,
			   Vec* arr2, unsigned vi, unsigned vf);

void Arr3AddVec(Arr3* arr, Vec* arr2, char dir[50]);
void Arr3SubVec(Arr3* arr, Vec* arr2, char dir[50]);
void Arr3MulVec(Arr3* arr, Vec* arr2, char dir[50]);
void Arr3DivVec(Arr3* arr, Vec* arr2, char dir[50]);

void Arr3AddMat(Arr3* arr, Mat* arr2, char dir[50]);
void Arr3SubMat(Arr3* arr, Mat* arr2, char dir[50]);
void Arr3MulMat(Arr3* arr, Mat* arr2, char dir[50]);
void Arr3DivMat(Arr3* arr, Mat* arr2, char dir[50]);

#endif
