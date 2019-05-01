typedef struct {
	int rows;
	int cols;
	float *values;
} matrix_t;

matrix_t *newMatrix(const int rows, const int cols);
matrix_t *import(const char *path);
matrix_t *newDummyMatrix(const int rows, const int cols);
matrix_t *newSquareMatrix(const int n);
matrix_t *newIdentity(const int n);
void destroyMatrix(matrix_t *m_ptr);
void printMatrix(matrix_t *m_ptr);
void printSerializedMatrix(matrix_t *m_ptr);
void setValue(matrix_t *m_ptr, const int row, const int col, const float value);
float getValue(matrix_t *m_ptr, const int row, const int col);
void transpose(matrix_t *m_ptr);
matrix_t *getTranspose(matrix_t *m_ptr);
matrix_t *getMinor(matrix_t *m_ptr, const int e_row, const int e_col);
float getCofactor(matrix_t *m_ptr, const int row, const int col);
matrix_t *getCofactorMatrix(matrix_t *m_ptr);
matrix_t *getAdjugateMatrix(matrix_t *m_ptr);
matrix_t *getInverseMatrix(matrix_t *m_ptr);
float getDeterminant(matrix_t *m_ptr);
