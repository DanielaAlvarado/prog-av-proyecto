#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float cofactor(float**, int, int, int);

void printMatrix(float **matrix, int n){
	for(int j = 0; j < n; j++){
		for(int i = 0; i < n; i++){
			printf("\t%f", matrix[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

float determinant(float **matrix, int n){
    if(n == 1){
        return matrix[0][0];
    }

    float det = 0;
    for(int j = 0; j < n; j++){
        det += matrix[0][j] * cofactor(matrix, n, 0, j);
    }

    return det;
}

float cofactor(float **matrix, int n, int row, int col){
    float **minor = (float **) calloc(n - 1, sizeof(float *));
    for(int i = 0; i < n - 1; i++){
        minor[i] = (float *) calloc(n - 1 , sizeof(float));
    }

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
    free(minor);
    return cof;
}

float **adjugate(float **matrix, int n){
    float **adj = (float **) calloc(n, sizeof(float *));
    for(int i = 0; i < n; i++){
        adj[i] = (float *) calloc(n, sizeof(float));
    }

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

    float **inv = (float **) calloc(n, sizeof(float *));
    for(int i = 0; i < n; i++){
        inv[i] = (float *) calloc(n, sizeof(float));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            inv[i][j] = adj[i][j] / det;
        }
    }

    free(adj);
    return inv;
}

int main(){
    float **matrix = (float **) calloc(3, sizeof(float *));
    for(int i = 0; i < 3; i++){
        matrix[i] = (float *) calloc(3 , sizeof(float));
    }

    matrix[0][0] = 2;
    matrix[0][1] = 4;
    matrix[0][2] = 3;
    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = -1;
    matrix[2][0] = 3;
    matrix[2][1] = 5;
    matrix[2][2] = 7;

    printMatrix(inverse(matrix, 3), 3);
}
