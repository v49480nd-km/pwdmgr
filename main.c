#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFFER 256
#define MAJOR 0
#define MINOR 3
#define PATCH 0
#define PWD_SIZE 18

/* TODO
   SEARCH FOR PASSWORD GIVEN NAME
   DELETE PASSWORD GIVEN NAME
   MASTER PASSWORD
   ENCRYPTION
   PROFIT */

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

void createPassword()
{
        char* name = (char*)malloc(sizeof(char) * 32);
        char* pwd = (char*)malloc(sizeof(char) * PWD_SIZE);

        if (pwd == NULL || name == NULL) {
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
                exit(EXIT_FAILURE);
        }

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

int main(int argc, char* argv[])
{
        if (argc <= 1) {
                printf("Not a command, please use pwdmgr -h for more info\n");
                exit(0);
        }

        for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--create") == 0) {
                        createPassword();
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
                        listPasswords();
                } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
                        printf("Version %d.%d.%d\n", MAJOR, MINOR, PATCH);
                } else {
                        printf("Not a command, please use pwdmgr -h for more info\n");
                        exit(0);
                }
        }

        return 0;
}
