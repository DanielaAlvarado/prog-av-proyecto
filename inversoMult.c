#include <stdio.h>
#include <stdlib.h>

void inputMatriz(int, float[][3]);
void matrizAdjunta(int, float[][3], float[][3], float[]);
void imprimirMatriz(int, float[][3]);
void matrizTranspuesta(int, float[][3], float[][3]);
float cofact(int, float, float[][3], float[]);
void inversa(int, float, float[][3], float[][3]);
void mult(int, float[][3], float[][3], float[][3]);

int main(){
	// La matriz solo puede ser de 3x3.
	int n = 3;
	float det = 0;

	// Matriz original, adjunta, y matriz de determinante.
	float a[n][n];
	float ma[n][n];
	float mt[n][n];
	float d[4] = {0, 0, 0, 0};
	float in[n][n];
	float r[n][n];


	// Se igualan los valores de las casillas de las matrices a 0.
	for(int j = 0; j < n; j++){
		for(int i = 0; i < n; i++){
			a[j][i]=0;
			ma[j][i]=0;
			mt[j][i]=0;
			r[j][i]=0;
		}
	}

	printf("\n\nEl numero de columnas y filas de A es de 3x3: \n");

	inputMatriz(n, a);
	matrizAdjunta(n, a, ma, d);
	matrizTranspuesta(n, ma, mt);
	det = cofact(n, det, a, d);
	inversa(n, det, in, mt);
	mult(n, a, in, r);

	printf("La matriz A es: \n");
	imprimirMatriz(n, a);

	printf("La matriz adjunta de A es: \n");
	imprimirMatriz(n, ma);

	printf("La matriz transpuesta de la adjunta de A es: \n");
	imprimirMatriz(n, mt);

	printf("El determinante de A es: %f\n\n", det);

	printf("La matriz inversa de A es: \n");
	imprimirMatriz(n, in);

	printf("La multiplicacion de la matriz inversa por A es: \n");
	imprimirMatriz(n, r);
}

//Input de los valores de la matriz.
void inputMatriz(int n, float a[][3]){
	int j, i;
	printf("\nEscribe el valor de cada una de las celdas de la matriz:\n");
	for(j = 0; j < n; j++){
		for(i = 0; i < n; i++){
			printf("\nEscribe el valor la celda que esta en la columna %d y en la fila %d: ", i, j);
			scanf("%f", &a[j][i]);
		}
	}
}

//Funcion que calcula la matriz adjunta
void matrizAdjunta(int n, float a[][3], float ma[][3], float d[]){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int z = 0;
			for(int k = 0; k < n; k++){
				if(k == i){
					k++;
				}
				for(int w = 0; w < n; w++){
					if(w == j){
						w++;
					}
					if(k < n && w < n){
						d[z] = a [k][w];
						z++;
					}
				}
			}

			//Se calcula el adjunto de cada casilla.
			int mu = (-1);
			for(int h = 0; h <= (j + i); h++){
				mu = -mu;
			}
			ma[i][j] = mu * (((d[0]) * (d[3])) - ((d[1]) * (d[2])));
		}
	}
}

void imprimirMatriz(int n, float a[][3]){
	for(int j = 0; j < n; j++){
		for(int i = 0; i < n; i++){
			printf("\t%f", a[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void matrizTranspuesta(int n, float ma[][3], float mt[][3]){
	for(int j = 0; j < n; j++){
		for(int i = 0; i < n; i++){
			mt[j][i] = ma[i][j];
		}
	}
}

float cofact(int n, float det, float a[][3],  float d[]){
	float cofact[3] = {0, 0, 0};

	int i = 0;
	for(int j = 0; j < n; j++){
		int z = 0;
		for(int k = 0; k < n; k++){
			if(k == i){
				k++;
			}
			for(int w = 0; w < n; w++){
				if(w == j){
					w++;
				}
				if(k < n && w < n){
					d[z] = a[k][w];
					z++;
				}
			}
		}

		//Se calcula el adjunto de cada casilla.
		int mu = -1;
		for(int h = 0; h <= j + i; h++){
			mu = -mu;
		}
		cofact[j] = mu * (((d[0]) * (d[3])) - ((d[1]) * (d[2]))) * a[i][j];
	}

	for(int j = 0; j < n; j++){
		det = cofact[j] + det;
	}

	return det;
}

void inversa(int n, float det, float in[][3], float mt[][3]){
	for(int j = 0; j < n; j++){
		for (int i = 0; i < n; i++){
			in[j][i] = mt[j][i] / det;
		}
	}
}

void mult(int n, float a[][3], float in[][3], float r[][3]){
	for(int j = 0; j < n; j++){
		for(int i = 0; i < n; i++){
			for(int k = 0; k < n; k++){
				r[j][i] = a[j][k] * in[k][i] + r[j][i];
			}
		}
	}
}
