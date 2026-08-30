#include <stdio.h>

#include "util/matrix.h"

void matrix_mul(int d11, int d12, int d21, int d22, double m1[d11][d12], double m2[d21][d22], double res[d11][d22]) {
	if (d12 != d21) {
		fprintf(stderr, "ERROR: d12 should match d21\n");
		return;
	}
	int res_dim1 = d11;
	int res_dim2 = d22;

	for (int i = 0; i < res_dim1; i++) {
		for (int j = 0; j < res_dim2; j++) {
			res[i][j] = 0;
			for (int k = 0; k < d12; k++) {
				res[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
}

