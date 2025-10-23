#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

int findPassword(char* name)
{
        char cur_line[BUFFER];
        char cur_name[strlen(name)];
        int line_num = 0;
        FILE* passes;
        passes = fopen("passwords", "r");

        while (fgets(cur_line, BUFFER, passes) != NULL) {
                line_num++;

                for (size_t i = 0; i < strlen(name); i++) {
                        cur_name[i] = cur_line[i];
                }

                if (strcmp(cur_name, name) == 0) {
                        fclose(passes);
                        return line_num;
                }
        }

        fclose(passes);
        return -1;
}

void checkMasterPassword()
{
        char master_pass[] = "./mass_pass";

        if (access(master_pass, F_OK) != 0) {
                setMasterPassword();
        }

        // get pass from user
        char* verify_pass = (char*)malloc(32 * sizeof(char));

        testAllocation(verify_pass);
        printf("Input master password to continue: ");
        scanf("%32s", verify_pass);

        char* verify_pass2 = (char*)realloc(verify_pass, strlen(verify_pass) * sizeof(char));

        testAllocation(verify_pass2);

        verify_pass = verify_pass2;
        // get pass from file
        FILE* mass_file;
        mass_file = fopen("mass_pass", "r");
        char* the_truth = (char*)malloc(32 * sizeof(char));

        testAllocation(the_truth);

        the_truth = fgets(the_truth, 32, mass_file);
        char* truth2 = (char*)realloc(the_truth, strlen(the_truth+1) * sizeof(char));

        testAllocation(truth2);

        the_truth = truth2;

        if (strcmp(verify_pass, the_truth) != 0) {
                printf("You are not the real person exiting program\n");
                free(verify_pass);
                free(the_truth);
                exit(0);
        }

        free(verify_pass);
        free(the_truth);
}

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

void deletePassword(int line_num)
{
        char cur_line[BUFFER];
        int cur_num = 0;
        FILE* old, new;
        old = fopen("passwords", "r");
        new = fopen("passwords2", "w");

        while (fgets(cur_line, BUFFER, old) != NULL) {
                cur_num++;

                if (cur_num == line_num)
                        continue;

                fputs(cur_line, BUFFER, new);
        }

        fclose(old);
        fclose(new);
        remove("passwords");
        rename("passwords2", "passwords");
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

void setMasterPassword()
{
        char* master_pass = (char*)malloc(32 * sizeof(char));

        testAllocation(master_pass);
        printf("Input a master password: ");
        scanf("%32s", master_pass);

        char* master_pass2 = (char*)realloc(master_pass, strlen(master_pass+1) * sizeof(char));

        testAllocation(master_pass2);
        
        master_pass = master_pass2;
        FILE* mass_pass;
        mass_pass = fopen("mass_pass", "w");
        
        fputs(master_pass, mass_pass);
        fclose(mass_pass);
        free(master_pass);
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
