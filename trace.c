#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void printMatrix(int** m, int r, int c){
	int i, j;
	for (i = 0; i < r; i++){
		for (j = 0; j < c; j++)
			printf("%d ", m[i][j]);
			//printf("%d ", *((m+i*c)+j));
		printf("\n");
	}
}

int vecMult(int* vA, int* vB, int n){
	int result = 0, i;
	for (i = 0; i < n; i++){
		result += vA[i] * vB[i];
	}
	return result;
}

int** matrixMult(int* mA, int rA, int cA, int* mB, int rB, int cB){
	int** result = malloc(rA * sizeof(int *)), i, j;
	for (i = 0; i < rA; i++) 
		result[i] = malloc(cB * sizeof(int));

	for (i = 0; i < rA; i++){
		for (j = 0; j < cB; j++){
			int vB[rA];
			int k;
			for (k = 0; k < rB; k++) {
				vB[k] = *((mB+k*cB) + j);
			}
			result[i][j] = vecMult(mA+i*cA, vB, cA);
		}
	}
	return result;
}

int trace(int** m, int n){
	int total = 0, i;
	for (i = 0; i < n; i++)
		total += m[i][i];
	return total;
}

int main(int argc, char** argv){
	if (argc <= 1) {
		printf("NO FILE PROVIDED\n");
		return 0;
	}
	if (access(*(argv+1), F_OK) != 0){
		printf("FILE DOES NOT EXIST\n");
		return 0;
	}
	FILE* f = fopen(argv[1], "r");
	int rowsA, colsA, rowsB, colsB, i , j;

	fscanf(f, "%d %d\n", &rowsA, &colsA);
	int matrixA[rowsA][colsA];
	for (i = 0; i < rowsA; i++)
		for (j = 0; j < colsA; j++)
			fscanf(f, " %d ", &matrixA[i][j]);

	fscanf(f, "%d %d\n", &rowsB, &colsB);
	int matrixB[rowsB][colsB];
	for (i = 0; i < rowsB; i++)
		for (j = 0; j < colsB; j++)
			fscanf(f, " %d ", &matrixB[i][j]);

	if (colsA != rowsB){
		printf("MULTIPLICATION NOT POSSIBLE\n");
		return 0;
	}

	int tra = trace(matrixMult((int*)matrixA, rowsA, colsA, (int*)matrixB, rowsB, colsB), rowsA);
	FILE* out = fopen("part2_trace.dat", "w");
	fprintf(out, "%d\n", tra);
	fclose(out);
	fclose(f);
	return 0;
}
