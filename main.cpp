#include <iostream>
#include <pthread.h>
#include <random>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include "gauss.h"

extern double **mat;
extern int m, n;
extern double *result;

unsigned long timediff(timeval t2, timeval t1) {
	return (t2.tv_sec - t1.tv_sec) * 1000000LL + (t2.tv_usec - t1.tv_usec);
}

int main(int argc, char **argv) {
	// srand(time(0));
	srand(0);

	timeval t1, t2, t3, t4;

	if (argc < 2) {
		std::cout << "NO!" << std::endl;
		return -1;
	}

	n = atoi(argv[1]);
	m = n + 1;

	mat = (double **) calloc(n, sizeof(double *));
	for (int i = 0; i < n; i++) {
		mat[i] = (double *) calloc(m, sizeof(double));
		for (int j = 0; j < m; j++) {
			mat[i][j] = (rand() % 10000) + 1 + ((double)rand() / (double)RAND_MAX);
		}
	}

	// n = 3;
	// m = 4;

	// mat = (double **) calloc(n, sizeof(double *));
	// for (int i = 0; i < n; i++) {
	// 	mat[i] = (double *) calloc(m, sizeof(double));
	// }
	// mat[0][0] = 3;	mat[0][1] = 3;	mat[0][2] = 4;	mat[0][3] = 1;
	// mat[1][0] = 3;	mat[1][1] = 5;	mat[1][2] = 9;	mat[1][3] = 2;
	// mat[2][0] = 5;	mat[2][1] = 9;	mat[2][2] = 17;	mat[2][3] = 4;

	// printmat(-1);

	gettimeofday(&t1, NULL);
	gauss_elim_openmp();
	gettimeofday(&t2, NULL);

	result = (double *) calloc(n, sizeof(double));

	gettimeofday(&t3, NULL);
	back_sub();
	gettimeofday(&t4, NULL);

	// for (int i = 0; i < n; i++) {
	// 	std::cout << result[i] << std::endl;
	// }

	std::cout << "forward elimination: " << timediff(t2, t1) << " microseconds" << std::endl;
	std::cout << "back substitution  : " << timediff(t4, t3) << " microseconds" << std::endl;

	free(result);
	for(int i = 0; i < n; i++) {
		free(mat[i]);
	}
	free(mat);

	return 0;
}

