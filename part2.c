#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv, char** envp){
	if (argc <= 1) {
		printf("NO FILE PROVIDED\n");
		return 0;
	}
	if (access(*(argv+1), F_OK) != 0){
		printf("FILE DOES NOT EXIST\n");
		return 0;
	}
	pid_t pid;
	FILE * fp;
	char buf[255];
	char* args[3];
	char* fibonacci = malloc(10 * sizeof(char));
	args[2] = NULL;
	args[1] = argv[1];
	while(1){
		printf("Which application would you like to run? (solver, trace, fib, quit, change): ");
		char temp[255] = "./";
		scanf(" %s", buf);

		if (strcmp(buf, "quit") == 0) 
			return 0;
		if (strcmp(buf, "change") == 0){
			printf("Enter the new file name: ");
			scanf(" %s", argv[1]);
			args[1] = argv[1];
		}
		else{
			if (strcmp(buf, "fib") == 0){
				fp = fopen(argv[1], "r");
				fscanf(fp, "%s", fibonacci);
				args[1] = fibonacci;
				fclose(fp);
			}
			args[0] = strcat(temp, buf);
			if ((pid = fork()) == 0){
				execve(args[0], args, envp);
				exit(0);
			}
			else
				waitpid(pid, NULL, 0); 
			wait(NULL);
		}
	}
	free(fibonacci);
	return 0;
}
