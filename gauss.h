#ifndef __GAUSS_H
#define __GAUSS_H

extern double **mat;
extern int m, n;
extern double *result;

// void gauss_elim(double **mat, int m, int n);
// void back_sub(double *result, double **mat, int m, int n);
void gauss_elim_openmp(void);
void gauss_elim_pthread(void);
void gauss_elim_single(void);
void back_sub(void);

void printmat(int pivot);

#endif
