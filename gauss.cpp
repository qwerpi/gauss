#include <iostream>
#include <pthread.h>
#include <stdint.h>
#include "gauss.h"

double **mat;
int n, m;
double *result;
int pivot;

void do_row(void *arg) {
	long row = (long)arg;
	double coef = mat[row][pivot] / mat[pivot][pivot];
	for (int j = pivot; j < m; j++) {
		mat[row][j] -= coef * mat[pivot][j];
	}
}

void gauss_elim() {
	// printmat(-1);

	pthread_t threads[n];

	for (int k = 0; k < n; k++) {
		double max = -1000000000.0;
		int i_max = 0;
		for (int i = k; i < n; i++) {
			if (abs(mat[i][k]) > max) {
				max = abs(mat[i][k]);
				i_max = i;
			}
		}
		if (mat[i_max][k] == 0) {
			std::cout << "Error: matrix is singular" << std::endl;
			return;
		}
		double *tmp = mat[k];
		mat[k] = mat[i_max];
		mat[i_max] = tmp;

		pivot = k;

		for (int i = k + 1; i < n; i++) {
			pthread_create(&threads[i], NULL, (void *(*)(void *))do_row, (void *)(long)i);
		}

		for (int i = k + 1; i < n; i++) {
			pthread_join(threads[i], NULL);
		}

		// printmat(k);
	}
}

void gauss_elim_single() {
	// printmat(-1);

	for (int k = 0; k < n; k++) {
		double max = -1000000000.0;
		int i_max = 0;
		for (int i = k; i < n; i++) {
			if (abs(mat[i][k]) > max) {
				max = abs(mat[i][k]);
				i_max = i;
			}
		}
		if (mat[i_max][k] == 0) {
			std::cout << "Error: matrix is singular" << std::endl;
			return;
		}
		double *tmp = mat[k];
		mat[k] = mat[i_max];
		mat[i_max] = tmp;

		pivot = k;

		for (int i = k + 1; i < n; i++) {
			double coef = mat[i][k] / mat[k][k];
			for (int j = k; j < m; j++) {
				mat[i][j] -= coef * mat[k][j];
			}
		}

		// printmat(k);
	}
}

void back_sub() {
	for (int i = n - 1; i >= 0; i--) {
		result[i] = mat[i][m - 1];
		for (int j = i + 1; j < n; j++) {
			result[i] -= mat[i][j] * result[j];
		}
		result[i] /= mat[i][i];
	}
}

void printmat(int pivot) {
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			if (i == pivot && j == pivot)
				std::cout << "\x1b[32m" << mat[j][i] << "\x1b[0m ";
				// printf("\x1b[32m%5.3f\x1b[0m ", mat[j][i]);
			else
				std::cout << mat[j][i] << " ";
				// printf("%5.3f ", mat[j][i]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}