#include <stdio.h>
#include <stdlib.h>


void inputMatriz(int, float[][3]);
void matrizAdjunta(int, float[][3], float[][3], float[]);
void imprimirMatriz(int, float[][3]);
void matrizTranspuesta(int, float[][3], float[][3]);
float cofact(int, float, float[][3], float[]);
void inversa(int, float, float[][3], float[][3]);
void mult(int, float[][3], float[][3], float[][3]);

int main()
{
	//La matriz sólo puede ser de 3x3.
	int N=3;
	float Determinante=0;

	//Matriz original, adjunta, y matriz de determinante.
	float A[N][N];
	float Ma[N][N];
	float Mt[N][N];
	float D[4]={0,0,0,0};
	float I[N][N];
	float R[N][N];


	//Se igualan los valores de las casillas de las matrices a 0.
	for(int j=0; j<N; j++)
	{
		for(int i=0; i<N; i++)
		{
				A[j][i]=0;
				Ma[j][i]=0;
				Mt[j][i]=0;
				R[j][i]=0;
		}
	}

	printf("\n\nEl número de columnas y filas de A es de 3x3: \n");

	inputMatriz(N, A);
	matrizAdjunta(N, A, Ma, D);
	matrizTranspuesta(N, Ma, Mt);
	Determinante = cofact(N, Determinante, A, D);
	inversa(N, Determinante, I, Mt);
	mult(N, A, I, R);

	printf("La matriz A es: \n");
	imprimirMatriz(N, A);

	printf("La matriz adjunta de A es: \n");
	imprimirMatriz(N, Ma);

	printf("La matriz transpuesta de la adjunta de A es: \n");
	imprimirMatriz(N, Mt);

	printf("El determinante de A es: %f\n\n", Determinante);

	printf("La matriz inversa de A es: \n");
	imprimirMatriz(N, I);

	printf("La multiplicacion de la matriz inversa por A es: \n");
	imprimirMatriz(N, R);

	system("PAUSE");
	return 0;
}

//Input de los valores de la matriz.
void inputMatriz(int N, float A[][3])
{
	int j, i;
	printf("\nEscribe el valor de cada una de las celdas de la matriz:\n");
	for(j=0; j<N; j++)
	{
		for(i=0; i<N; i++)
		{
			printf("\nEscribe el valor la celda que esta en la columna %d y en la fila %d: ", i, j);
			scanf("%f", &A[j][i]);
		}
	}
}

//Función que calcula la matriz adjunta
void matrizAdjunta(int N, float A[][3], float Ma[][3], float D[])
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			int z=0;
			for(int k=0; k<N; k++)
			{
				if(k==i)
				{
					k++;
				}
				for(int w=0; w<N; w++)
				{
					if(w==j)
					{
						w++;
					}
					if(k<N && w<N)
					{
						D[z]=A[k][w];
						z++;
					}
				}
			}

			//Se calcula el adjunto de cada casilla.
			int mu=(-1);
			for(int h=0; h<=(j+i); h++)
			{
				mu=mu*(-1);
			}
			Ma[i][j]=mu*(((D[0])*(D[3]))-((D[1])*(D[2])));
		}
	}
}

void imprimirMatriz(int N, float A[][3])
{
	for(int j=0; j<N; j++)
	{
		for(int i=0; i<N; i++)
		{
			printf("\t%f", A[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void matrizTranspuesta(int N, float Ma[][3], float Mt[][3])
{
	for(int j=0; j<N; j++)
	{
		for(int i=0; i<N; i++)
		{
			Mt[j][i]=Ma[i][j];
		}
	}
}

float cofact(int N, float Determinante, float A[][3],  float D[])
{
	float cofact[3]={0,0,0};

	int i=0;
	for(int j=0; j<N; j++)
	{
		int z=0;
		for(int k=0; k<N; k++)
		{
			if(k==i)
			{
				k++;
			}
			for(int w=0; w<N; w++)
			{
				if(w==j)
				{
					w++;
				}
				if(k<N && w<N)
				{
					D[z]=A[k][w];
					z++;
				}
			}
		}

		//Se calcula el adjunto de cada casilla.
		int mu=(-1);
		for(int h=0; h<=(j+i); h++)
		{
			mu=mu*(-1);
		}
		cofact[j]=mu*(((D[0])*(D[3]))-((D[1])*(D[2])))*A[i][j];
	}

	for(int j=0; j<N; j++)
	{
		Determinante=cofact[j]+Determinante;
	}

	return Determinante;
}

void inversa(int N, float Determinante, float I[][3], float Mt[][3])
{
	for (int j=0; j<N; ++j)
	{
		for (int i=0; i<N; ++i)
		{
			I[j][i]=Mt[j][i]/Determinante;
		}
	}
}

void mult(int N, float A[][3], float I[][3], float R[][3])
{
	for(int j=0; j<N; j++)
	{
		for(int i=0; i<N; i++)
		{
			for(int k=0; k<N; k++)
			{
				R[j][i] = A[j][k]*I[k][i]+R[j][i];
			}
		}
	}
}
