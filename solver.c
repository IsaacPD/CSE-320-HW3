#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

double* coefficients;
int n;

double evaluate(double x){
	double result = 0;
	int i;
	for (i = 0; i <= n; i++)
		result += coefficients[i] * pow(x, n - i);
	return result;
}

double bisection(double a, double b, double tol){
	while(1){
		double c = (a + b)/2;
		double r = evaluate(c);
		if (r == 0.0 || (b - a)/2 < tol)
			return c;
		if ((evaluate(a) > 0) == (r > 0))
			a = c;
		else
			b = c;
	}
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
	double a, b, tol;
	fscanf(f, "%d %lf %lf %lf ", &n, &tol, &a, &b);
	coefficients = malloc((n+1) * sizeof(double));
	int i;
	for (i = 0; i <= n; i++)
		fscanf(f, "%lf ", &coefficients[i]);

	double root = bisection(a, b, tol);
	
	FILE* out = fopen("part2_solver.dat", "w");
	fprintf(out, "%lf", root);
	fclose(f);
	fclose(out);
	free(coefficients);
	return 0;
}
