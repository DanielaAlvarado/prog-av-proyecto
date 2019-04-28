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

//	Function declarations
void setValue(matrix_t *m_ptr, const int row, const int col, const int value);

/**
	New Matrix
	Allocates space for a matrix and its values.
	@param	rows	Rows in the matrix.
	@param	cols	Columns in the matrix.
	@return			Pointer to the new matrix.	
*/
matrix_t *newMatrix(const int rows, const int cols) {
	matrix_t *m_ptr = (matrix_t *)malloc(sizeof(matrix_t));
	m_ptr->rows = rows;
	m_ptr->cols = cols;
	
	int *m_values = (int *)calloc(rows * cols, sizeof(int));
	m_ptr->values = m_values;
	
	return m_ptr;
}

/**
	New Square Matrix
	Allocates space for a square matrix and its values.
	@param	n	Dimension of the square matrix.
	@return		Pointer to the new matrix.
*/
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

/**
	New Identity Matrix
	Creates an identity matrix.
	@param	n	Dimension of the identity matrix.
	@return		Pointer to the new identity matrix.
*/
matrix_t *newIdentity(const int n) {
	matrix_t *m_ptr = newSquareMatrix(n);
	for(int i = 0; i < n; i++) {
		setValue(m_ptr, i, i, 1);
	}
	
	return m_ptr;
}

/**
	Destroy Matrix
	Frees up space used by matrix.
	@param	m_ptr	Pointer to the matrix to destroy.
*/
void destroyMatrix(matrix_t *m_ptr) {
	free(m_ptr);
}

/**
	Print Matrix
	Prints the matrix to screen.
	@param	m_ptr	Pointer to the matrix to print.
*/
void printMatrix(matrix_t *m_ptr) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			printf("%d  ", m_ptr->values[i * rows + j]);
		}
		printf("\n");
	}
	printf("\n");
}

/**
	Set Value
	Sets the value of the indicated element in the matrix.
	@param	m_ptr	Pointer to the matrix to perform the operation on.
	@param	row		Row in which the element's value will be set.
	@param	col		Column in which the element's value will be set.
	@param	value	Value to be set on the element.
*/
void setValue(matrix_t *m_ptr, const int row, const int col, const int value) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	assert(row < rows);
	assert(col < cols);
	
	m_ptr->values[row * rows + col] = value;
}

/**
	Get Value
	Get the value of the indicated element in the matrix.
	@param	m_ptr	Pointer to the matrix to perform the operation on.
	@param	row		Row in which the element is located.
	@param	col		Column in which the element is located.
	@return			Value of the indicated element.
*/
int getValue(matrix_t *m_ptr, const int row, const int col) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	assert(row < rows);
	assert(col < cols);
	
	return m_ptr->values[row * rows + col];
}

/**
	Transpose
	Transpose given matrix. Given matrix will be overwritten.
	@param	m_ptr	Pointer to the matrix to be transposed.
*/
void transpose(matrix_t *m_ptr) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	assert(rows == cols);
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < i; j++) {
			int temp = getValue(m_ptr, i, j);
			//	Swap
			setValue(m_ptr, i, j, getValue(m_ptr, j, i));
			setValue(m_ptr, j, i, temp);
		}
	}
}

/**
	Get Transpose
	Get the transpose of the given matrix. A new matrix will be returned.
	@param	m_ptr	Pointer to the matrix to get the transpose of.
	@return			Transposed matrix.
*/
matrix_t *getTranspose(matrix_t *m_ptr) {
	printf("Not implemented yet :(\n");
	exit(-1);
}

/**
	Some testing and debugging...
*/
int main(int argc, char *argv[]) {
//	matrix_t *a_ptr = newMatrix(3, 4);
//	setValue(a_ptr, 1, 2, 5);
//	printMatrix(a_ptr);
//	printf("%d\n", getValue(a_ptr, 1, 2));
//	destroyMatrix(a_ptr);
	
//	matrix_t *b_ptr = newIdentity(4);
//	printMatrix(b_ptr);
//	destroyMatrix(b_ptr);
	
	matrix_t *c_ptr = newSquareMatrix(4);
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			setValue(c_ptr, i, j, i * 4 + j + 1);
		}
	}
	
	printMatrix(c_ptr);
	transpose(c_ptr);
	printMatrix(c_ptr);
}
