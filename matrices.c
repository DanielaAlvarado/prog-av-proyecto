#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
	Matrix
	
	Some convenient functions for handling matrices as a type.
	
	@author		A01329233	Daniela Alvarado Pereda
	@author		A01328937	Luis Francisco Flores Romero
	@since		26.apr.19
*/

typedef struct {
	int rows;
	int cols;
	int *values;
} matrix_t;

matrix_t *newMatrix(const int rows, const int cols) {
	matrix_t *m_ptr = (matrix_t *)malloc(sizeof(matrix_t));
	m_ptr->rows = rows;
	m_ptr->cols = cols;
	
	int *m_values = (int *)calloc(rows * cols, sizeof(int));
	m_ptr->values = m_values;
	
	return m_ptr;
}

matrix_t *newSquareMatrix(const int n) {
//	Allocate space for matrix struct and init
	matrix_t *m_ptr = (matrix_t *)malloc(sizeof(matrix_t));
	m_ptr->rows = n;
	m_ptr->cols = n;
	
//	Allocate space for matrix values and init
	int *m_values = (int *)calloc(n * n, sizeof(int));
//	Link values space to matrix struct
	m_ptr->values = m_values;
	
	return m_ptr;
}

void destroyMatrix(matrix_t *m_ptr) {
	free(m_ptr);
}

void printMatrix(matrix_t *m_ptr) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			printf("%d ", m_ptr->values[i * rows + j]);
		}
		printf("\n");
	}
	printf("\n");
}

void setValue(matrix_t *m_ptr, const int row, const int col, const int value) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	assert(row < rows);
	assert(col < cols);
	
	m_ptr->values[row * rows + col] = value;
}

int getValue(matrix_t *m_ptr, const int row, const int col) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	assert(row < rows);
	assert(col < cols);
	
	return m_ptr->values[row * rows + col];
}

int main(int argc, char *argv[]) {
	matrix_t *a_ptr = newMatrix(3, 4);
	setValue(a_ptr, 1, 2, 5);
	printMatrix(a_ptr);
	printf("%d\n", getValue(a_ptr, 1, 2));
	destroyMatrix(a_ptr);
}
