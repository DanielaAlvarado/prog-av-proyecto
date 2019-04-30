#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/**
	Matrix
	
	Some convenient functions for handling matrices as a type.
	
	@author		A01329233	Daniela Alvarado Pereda
	@author		A01328937	Luis Francisco Flores Romero
	@since		29.apr.19
*/

typedef struct {
	int rows;
	int cols;
	int *values;
} matrix_t;

//	Function declarations
void setValue(matrix_t *, const int, const int, const int);
int getValue(matrix_t *, const int, const int);
int getDeterminant(matrix_t *);

/**
	New Matrix
	Allocates space for a matrix and its values.
	@param	rows	Rows in the matrix.
	@param	cols	Columns in the matrix.
	@return			Pointer to the new matrix.	
*/
matrix_t *newMatrix(const int rows, const int cols) {
	assert(rows > 0);
	assert(cols > 0);
	
	//	Allocate space for matrix struct and init
	matrix_t *m_ptr = (matrix_t *)malloc(sizeof(matrix_t));
	m_ptr->rows = rows;
	m_ptr->cols = cols;
	
	//	Allocate space for matrix values and init
	int *m_values = (int *)calloc(rows * cols, sizeof(int));
	//	Link values space to matrix struct
	m_ptr->values = m_values;
	
	return m_ptr;
}

/**
	Import
	Reads a file and creates a new matrix from its content. Please note the file
	should be correctly formatted.
	@param	path	The path to the file describing the matrix.
	@return			Matrix generated from file.
*/
matrix_t *import(const char *path) {
	FILE *f_ptr = fopen(path, "r");
	if(f_ptr == NULL) {
		printf("Couldn't open file: %s\n", path);
	}
	
	int rows;
	int cols;
	fscanf(f_ptr, "%d", &rows);
	fscanf(f_ptr, "%d", &cols);
	matrix_t *m_ptr = newMatrix(rows, cols);
	
	int element;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++){
			if(fscanf(f_ptr, "%d", &element) != 1) {
				printf("%s: File is damaged or not correctly formatted\n", path);
				return NULL;
			}
			setValue(m_ptr, i, j, element);
		}
	}
	
	fclose(f_ptr);
	return m_ptr;
}

/**
	New Dummy Matrix
	Creates a dummy matrix of given dimensions. Useful for testing. This matrix
	will contain elements starting in 1 and increasing top-to-bottom,
	left-to-right.
	@param	rows	Rows of the matrix.
	@param	cols	Columns of the matrix.
	@return			A new dummy matrix.
*/
matrix_t *newDummyMatrix(const int rows, const int cols) {
	matrix_t *m_ptr = newMatrix(rows, cols);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			int element = (cols * i) + j + 1;
			setValue(m_ptr, i, j, element);
		}
	}
	
	return m_ptr;
}

/**
	New Square Matrix
	Allocates space for a square matrix and its values.
	@param	n	Dimension of the square matrix.
	@return		Pointer to the new matrix.
*/
matrix_t *newSquareMatrix(const int n) {
	return newMatrix(n, n);
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
	free(m_ptr->values);
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
			printf("\t%d", getValue(m_ptr, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

/**
	Print serialized matrix
	Prints a serialized version of given matrix. Useful for debugging.
	@param	m_ptr	Pointer to the matrix to be serialized.
*/
void printSerializedMatrix(matrix_t *m_ptr) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	for(int i = 0; i < rows * cols; i++) {
		printf("%d ", m_ptr->values[i]);
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
	
	m_ptr->values[(row * cols) + col] = value;
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
	
	return m_ptr->values[row * cols + col];
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
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	assert(rows == cols);
	
	matrix_t *t_ptr = newSquareMatrix(rows);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			setValue(t_ptr, i, j, getValue(m_ptr, j, i));
		}
	}
	
	return t_ptr;
}

/**
	Get Minor
	Creates a new matrix representing the minor of the designated element in the
	given matrix.
	@param	m_ptr	Pointer to the matrix from which to get the minor.
	@param	e_row	Row of the designated element.
	@param	e_col	Column of the designated element.
*/
matrix_t *getMinor(matrix_t *m_ptr, const int e_row, const int e_col) {
	int m_rows = m_ptr->rows;
	int m_cols = m_ptr->cols;
	
	assert(e_row >= 0);
	assert(e_row < m_rows);
	assert(e_col >= 0);
	assert(e_col < m_cols);
	
	matrix_t *minor_ptr = newMatrix(m_rows - 1, m_cols - 1);
	
	int min_row = 0;
	int min_col;
	for(int i = 0; i < m_rows; i++) {
		if(i == e_row)
			continue;
		
		min_col = 0;
		for(int j = 0; j < m_cols; j++) {
			if(j == e_col)
				continue;
			
			setValue(minor_ptr, min_row, min_col, getValue(m_ptr, i, j));
			min_col++;
		}
		
		min_row++;
	}
	
	return minor_ptr;
}

/**
	Get Cofactor
	Computes the cofactor of the designated element in the given matrix.
	@param	m_ptr	Pointer to the matrix containing the element from which to get the cofactor.
	@param	row		Row of the designated element.
	@param	col		Column of the designated element.
	@return			Cofactor of the designated element.
*/
int getCofactor(matrix_t *m_ptr, const int row, const int col) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	assert(rows == cols);
	
	matrix_t *minor = getMinor(m_ptr, row, col);
	int cofactor = (int)pow(-1, row + col) * getDeterminant(minor);
	destroyMatrix(minor);
	return cofactor;
}

/**
	Get Cofactor Matrix
	Computes the cofactor matrix of given matrix.
	@param	m_ptr	Matrix to get the cofactor matrix of.
	@return			The cofactor matrix.
*/
matrix_t *getCofactorMatrix(matrix_t *m_ptr) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	//	Check a square matrix was given
	assert(rows == cols);
	
	matrix_t *comatrix = newSquareMatrix(rows);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			setValue(comatrix, i, j, getCofactor(m_ptr, i, j));
		}
	}
	
	return comatrix;
}

/**
	Get Adjugate Matrix
	Computes the adjugate of given matrix.
	@param	m_ptr	The matrix to get the adjugate of.
	@return			The adjugate matrix.
*/
matrix_t *getAdjugateMatrix(matrix_t *m_ptr) {
	matrix_t *adjugate = getCofactorMatrix(m_ptr);
	transpose(adjugate);
	
	return adjugate;
}

/**
	Get Inverse Matrix
	Computes the inverse of the given matrix.
	@param	m_ptr	Pointer to the matrix to get the inverse of.
	@return			The inverse of the given matrix.
*/
matrix_t *getInverseMatrix(matrix_t *m_ptr) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	//	Check a square matrix was given
	assert(rows == cols);
	
	matrix_t *inverse = newSquareMatrix(rows);
	matrix_t *adjugate = getAdjugateMatrix(m_ptr);
	int determinant = getDeterminant(m_ptr);
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			int element = getValue(adjugate, i, j) / determinant;
			setValue(inverse, i, j, element);
		}
	}
	
	destroyMatrix(adjugate);
	return inverse;
}

/**
	Get Determinant
	Computes the determinant of given matrix.
	@param	m_ptr	Pointer to the matrix to get the determinant of.
	@return			Determinant of the given matrix.
*/
int getDeterminant(matrix_t *m_ptr) {
	int rows = m_ptr->rows;
	int cols = m_ptr->cols;
	
	assert(rows == cols);
	
	if(rows == 1)
		return getValue(m_ptr, 0, 0);
	
	int determinant = 0;
	for(int j = 0; j < cols; j++) {
		//	Compute determinant from first row elements
		determinant += getValue(m_ptr, 0, j) * getCofactor(m_ptr, 0, j);
	}
	
	return determinant;
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
	
//	matrix_t *c_ptr = newDummyMatrix(4, 4);
	
//	printMatrix(c_ptr);
//	printSerializedMatrix(c_ptr);
//	transpose(c_ptr);
//	printMatrix(c_ptr);
	
	matrix_t *d_ptr = import("matrix.mat");
	matrix_t *inverse = getInverseMatrix(d_ptr);
	printMatrix(inverse);
	
//	matrix_t *e_ptr = newSquareMatrix(3);
//	setValue(e_ptr, 0, 2, 5);
//	setValue(e_ptr, 1, 1, 3);
//	setValue(e_ptr, 2, 0, 2);
//	printMatrix(e_ptr);
//	printSerializedMatrix(e_ptr);
}
