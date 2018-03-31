#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/wait.h>

struct wallets {
    uint32_t key;
    int money;
};

void print_help() {}

uint32_t key_gen() {
    uint32_t key = rand() & 0xff;
    key |= (rand() & 0xff) << 8;
    key |= (rand() & 0xff) << 16;
    key |= (rand() & 0xff) << 24;

    return key;
}

uint32_t money_gen() {
    uint32_t money = rand() % 100;

    return money;
}

void generate_wallets(struct wallets* wallet, int num) {
    int i = 0;
    int num_wallets = num;
    for (i; i < num_wallets; ++i) {
        wallet[i].key = key_gen();
        wallet[i].money = money_gen();
    }
}

void print_wallets(FILE* fp, int num_wallets, struct wallets* wallet) {
    int i = 0;
    for (i; i < num_wallets; ++i)
        fprintf(fp, "wallet: %x; money: %u\n", wallet[i].key, wallet[i].key);
}

int main(void) {
    printf("Welcome to the BTC wallet tracker.\n");
    srand(time(NULL));

    char* filename = (char*)malloc(255);
    char* command = (char*)malloc(255);
	char* args[3];
	args[2] = NULL;
    FILE* fp = NULL;
    int num_wallets;
    int is_generated = 0;
    int is_printed = 0;
    pid_t pid;

    printf("Please enter the file name that contains number of wallets: ");
    scanf("%s", filename);
	if (access(filename, F_OK) != 0){
		printf("File does not exist\n");
		exit(0);
	}
    fp = fopen(filename, "r");
    fscanf(fp, "%d", &num_wallets);
    struct wallets* wallet = (struct wallets*)malloc(num_wallets * sizeof(struct wallets));
	fclose(fp);

    printf("Type 'help' for list of available commands.\n");
prompt:
    printf("prompt> ");
    scanf("%s", command);
    if (strcmp(command, "help") == 0) {
        if ((pid = fork()) == 0) {
            execvp("./print_help", args);
            exit(0);
        }
		waitpid(pid, NULL, 0);
        sleep(1);
        goto prompt;
    }
    else if (strcmp(command, "generate") == 0) {
        if (!is_generated) {
            is_generated = 1;
            generate_wallets(wallet, num_wallets);
        }
        else
            printf("Wallets are already generated.\n");
        goto prompt;
    }
    else if (strcmp(command, "print") == 0) {
        if (!is_printed) {
            is_printed = 1;
            char* fileout = "wallets_info.dat";
            fp = fopen(fileout, "w");
            print_wallets(fp, num_wallets, wallet);
			fclose(fp);
        }
        else
            printf("Wallets are already printed.\n");
        goto prompt;
    }
    else if (strcmp(command, "quit") == 0){
		free(command);
		free(filename);
		free(wallet);
        return 0;
	}
    else {
        printf("Unknown command.\n");
        goto prompt;
    }

    return 0;
}
