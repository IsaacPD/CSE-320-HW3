#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

long int fib(unsigned long int* nums, int n){
	if (nums[n] != 0) 
		return nums[n];
	nums[n] = fib(nums, n-1) + fib(nums, n-2);
	return nums[n];
}

int main(int argc, char** argv){
	if (argc <= 1){
		printf("INVALID ARGUMENTS\n");
		return 0;
	}
	int n = atoi(argv[1]);
	if (n < 1) {
		printf("INVALID ARGUMENT\n");
		return 0;
	}
	unsigned long int * fibS = calloc(n, sizeof(unsigned long int));
	fibS[0] = 1;
	fibS[1] = 1;
	unsigned long int result = fib(fibS, n - 1);
	FILE* f = fopen("part2_fib.dat", "w");
	fprintf(f, "%lu\n", result);
	fclose(f);
	free(fibS);
	return 0;
}
