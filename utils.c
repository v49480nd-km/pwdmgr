#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

void createPassword()
{
        char* name = (char*)malloc(sizeof(char) * BUFFER);
        char* pwd = (char*)malloc(sizeof(char) * PWD_SIZE);

        testAllocation(name);
        testAllocation(pwd);
        printf("Input name for password: ");
        scanf("%32s", name);
        testAllocation(name);

        char* name2 = (char*)realloc(name, strlen(name+1) * sizeof(char));

        testAllocation(name2);

        name = name2;
        const char CHARS[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const char NUMS[11] = "1234567890";
        const char SYMBOLS[11] = "!@#$%^&*()";
        int random = rand() % 3;

        srand(time(NULL));

        for (int i = 0; i < PWD_SIZE; i++) {
                if (random == 0) {
                        pwd[i] = CHARS[rand() % 52];
                        random = rand() % 3;
                        continue;
                } else if (random == 1) {
                        pwd[i] = NUMS[rand() % 10];
                        random = rand() % 3;
                        continue;
                } else if (random == 2) {
                        pwd[i] = SYMBOLS[rand() % 10];
                        random = rand() % 3;
                        continue;
                }
        }

        storePassword(name, pwd);
}

void listPasswords()
{
        char pass_file[] = "./passwords";
        char buffer[BUFFER];

        if (access(pass_file, F_OK) != 0) {
                printf("File does not exist, please create a password to store\n");
                exit(0);
        }

        FILE* password_file;
        password_file = fopen(pass_file, "r");

        if (password_file == NULL) {
                printf("Failed to open password file\n");
                exit(EXIT_FAILURE);
        }

        while (fgets(buffer, BUFFER, password_file) != NULL) {
                printf("%s", buffer);
        }
}

void storePassword(char* name, char* pwd)
{
        FILE* password_file;
        password_file = fopen("passwords", "a");

        if (password_file == NULL) {
                printf("Error storing password, exiting program\n");
                exit(EXIT_FAILURE);
        }

        fputs(name, password_file);
        fputs(":", password_file);
        fputs(pwd, password_file);
        fputs("\n", password_file);
        fclose(password_file);
        free(name);
        free(pwd);
}

void testAllocation(char* test_var)
{
        if (test_var == NULL) {
                printf("ERROR, exiting program!\n");
                exit(EXIT_FAILURE);
        }
}
