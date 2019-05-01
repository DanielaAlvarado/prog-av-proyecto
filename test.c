#include <stdio.h>
#include <matrices.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	matrix_t *d_ptr = import("matrix.mat");
    double avTime = 0;
    FILE *ptf = fopen("log.txt", "w+");

    if(ptf){
        for(int i = 0; i < 10; i++){
            double startTime = omp_get_wtime();
            matrix_t *inverse = getInverseMatrix(d_ptr);
            double runningTime = omp_get_wtime() - startTime;

            fprintf(ptf, "Run %d time: %f\n", i + 1, runningTime);
            avTime += runningTime;

            if(i == 9){
                printMatrix(inverse);
            }
            destroyMatrix(inverse);
        }

        avTime /= 10;
        printf("Average time: %f\n", avTime);
    }else{
        printf("Error while opening log file\n");
    }
}
