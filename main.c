#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAJOR 0
#define MINOR 1
#define PATCH 3
#define PWD_SIZE 18

/* TODO
   pass commands when running it
   STORE PASSWORD WITH NAME
   LIST PASSWORDS
   SEARCH FOR PASSWORD GIVEN NAME
   DELETE PASSWORD GIVEN NAME
   MASTER PASSWORD
   ENCRYPTION
   PROFIT */


void createPassword(char* name, char* pwd)
{
        const char CHARS[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const char NUMS[11] = "1234567890";
        const char SYMBOLS[11] = "!@#$%^&*()";
        int random = rand() % 3;

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
}

int main(int argc, char* argv[])
{
        if (argc <= 1) {
                printf("Not a command, please use pwdmgr -h for more info\n");
                exit(0);
        }

        for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--create") == 0) {
                        char* name = (char*)malloc(sizeof(char) * 32);
                        char* new_pwd = (char*)malloc(sizeof(char) * PWD_SIZE);

                        if (new_pwd == NULL || name == NULL) {
                                printf("Failure creating password, exiting program\n");
                                exit(EXIT_FAILURE);
                        }
                        
                        printf("Input name for password: ");
                        scanf("%32s", name);

                        if (name == NULL) {
                                printf("Failure to retrieve name, exiting program\n");
                                exit(EXIT_FAILURE);
                        }

                        char* name2 = (char*)realloc(name, strlen(name+1) * sizeof(char));

                        if (name2 == NULL) {
                                printf("Failure to retrieve name, exiting program\n");
                        }

                        name = name2;
                        srand(time(NULL));
                        createPassword(name, new_pwd);
                        free(new_pwd);
                        free(name);
                } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delete") == 0) {
                        char* name = (char*)malloc(sizeof(char) * 32);
                        printf("Input name to delete: ");
                        scanf("%32s", name);

                        if (name == NULL) {
                                printf("Failure getting name, exiting program\n");
                                exit(EXIT_FAILURE);
                        }

                        char* name2 = (char*)realloc(name, strlen(name+1) * sizeof(char));

                        if (name2 == NULL) {
                                printf("Failure getting name, exiting program\n");
                                exit(EXIT_FAILURE);
                        }

                        name = name2;
                        printf("Deleting: %s\n", name);
                        free(name);
                } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--find") == 0) {
                        char* name = (char*)malloc(sizeof(char) * 32);
                        printf("Input name to find: ");
                        scanf("%32s", name);

                        if (name == NULL) {
                                printf("Failure getting name, exiting program\n");
                                exit(EXIT_FAILURE);
                        }

                        char* name2 = (char*)realloc(name, strlen(name+1) * sizeof(char));

                        if (name2 == NULL) {
                                printf("Failure getting name, exiting program\n");
                                exit(EXIT_FAILURE);
                        }

                        name = name2;
                        printf("Finding: %s\n", name);
                        free(name);
                } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                        printf(
                                "-c, --create -> creates a password and stores it automatically\n"
                                "-d, --delete -> given a name finds and deletes password from storage\n"
                                "-f, --find -> given a name finds that specific password\n"
                                "-h, --help -> displays this very menu\n"
                                "-l, --list -> lists all passwords\n"
                                "-v, --version -> displays current version\n"
                        );
                } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--list") == 0) {
                        printf("Listing passwords\n");
                } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
                        printf("Version %d.%d.%d\n", MAJOR, MINOR, PATCH);
                } else {
                        printf("Not a command, please use pwdmgr -h for more info\n");
                        exit(0);
                }
        }

        return 0;
}
