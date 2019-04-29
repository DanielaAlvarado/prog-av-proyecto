#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

float cofactor(float**, int, int, int);

float determinant(float **matrix, int n){
    if(n == 1){
        return matrix[0][0];
    }

    float det = 0;
	// #pragma omp parallel for reduction(+:det)
	for(int j = 0; j < n; j++){
		det += matrix[0][j] * cofactor(matrix, n, 0, j);
	}

    return det;
}

float **createMatrix(int n){
	float **matrix = (float **) calloc(n, sizeof(float *));
	// #pragma omp parallel for
    for(int i = 0; i < n; i++){
        matrix[i] = (float *) calloc(n, sizeof(float));
    }

	return matrix;
}

void destroyMatrix(float **matrix, int n){
	// #pragma omp parallel for
    for(int i = 0; i < n; i++){
        free(matrix[i]);
    }

	free(matrix);
}

float cofactor(float **matrix, int n, int row, int col){
    float **minor = createMatrix(n - 1);

    int mi = 0;
    for(int i = 0; i < n; i++){
        if(i != row){
            int mj = 0;
            for(int j = 0; j < n; j++){
                if(j != col){
                    minor[mi][mj] = matrix[i][j];
                    mj++;
                }
            }

            mi++;
        }
    }

    float cof = pow(-1, col + row + 2) * determinant(minor, n - 1);
    destroyMatrix(minor, n - 1);
    return cof;
}

float **adjugate(float **matrix, int n){
    float **adj = createMatrix(n);

	// #pragma omp parallel for collapse(2)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            adj[i][j] = cofactor(matrix, n, j, i);
        }
    }

    return adj;
}

float **inverse(float **matrix, int n){
    float **adj = adjugate(matrix, n);
    float det = determinant(matrix, n);

    float **inv = createMatrix(n);

	// #pragma omp parallel for collapse(2)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            inv[i][j] = adj[i][j] / det;
        }
    }

    destroyMatrix(adj, n);
    return inv;
}


void printMatrix(float **matrix, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("\t%f", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(){
	double start_time = omp_get_wtime();

	int n = 5;
	float **matrix = createMatrix(n);

    matrix[0][0] = 5;
    matrix[0][1] = 9;
    matrix[0][2] = 8;
    matrix[0][3] = 8;
    matrix[0][4] = 5;
	matrix[1][0] = 0;
    matrix[1][1] = 7;
    matrix[1][2] = 0;
    matrix[1][3] = 9;
    matrix[1][4] = 3;
	matrix[2][0] = 4;
    matrix[2][1] = 7;
    matrix[2][2] = 9;
    matrix[2][3] = 0;
    matrix[2][4] = 0;
	matrix[3][0] = 9;
    matrix[3][1] = 1;
    matrix[3][2] = 6;
    matrix[3][3] = 1;
    matrix[3][4] = 8;
	matrix[4][0] = 4;
    matrix[4][1] = 7;
    matrix[4][2] = 6;
    matrix[4][3] = 6;
    matrix[4][4] = 5;

	float **inv = inverse(matrix, n);
	printMatrix(inv, n);
	destroyMatrix(matrix, n);
	destroyMatrix(inv, n);

	double time = omp_get_wtime() - start_time;
	printf("%f\n", time);
}
