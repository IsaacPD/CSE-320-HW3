#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

void mode2(){
	printf("Mode 2 (create, clean, date, exit): ");
}

void mode1(){
	printf("Mode 1 (start, exit): ");
}

int main(int argc, char** argv){
	pid_t pid1, pid2;
	int pipefd[] = {12, 16};
	char in[128];

	if (pipe(pipefd) < 0){
		perror("Pipe error: ");
		return -1;
	}

	while (1){
		mode1();
		scanf("%s", in);
		if (strcmp(in, "start") == 0){
			if ((pid1 = fork()) == 0){
				close(pipefd[1]);
				while(1){
					read(pipefd[0], in, 128);
				
					if (strcmp(in, "create") == 0){
						if ((pid2 = fork()) == 0){
							printf("%d\n", getpid());
							exit(0);
						}
					} else if (strcmp(in, "clean") == 0){
						while (waitpid(-1, NULL, 0) > 0);
					} else if (strcmp(in, "date") == 0){
						char buff[100];
					   	time_t d = time(NULL);
						strftime(buff, 100, "%Y-%m-%d", localtime(&d));
						printf("%s\n", buff);
					} else if (strcmp(in, "exit") == 0){
						close(pipefd[0]);
						exit(0);
					}
					in[0] = '[';
				}
			} else {
				while (1){
					mode2();
					scanf("%s", in);
					write(pipefd[1], in, 256);
					if (waitpid(pid1, NULL, WNOHANG) > 0 || strcmp(in, "exit") == 0){
						wait(NULL);
						break;
					}
				}
			}
		} else if (strcmp(in, "exit") == 0){
			close(pipefd[1]);
			return 0;
		}
	}
}
