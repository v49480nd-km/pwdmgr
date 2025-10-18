#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PWD_SIZE 18

/* TODO
   pass commands when running it
   STORE PASSWORD WITH NAME
   LIST PASSWORDS
   SEARCH FOR PASSWORD GIVEN NAME
   DELETE PASSWORD GIVEN NAME
   MASTER PASSWORD
   PROFIT */

/* COMMANDS
   -h -> help
   -c -> create
   -l -> list
   -f <name> -> find
   -d <name> -> find */

void createPassword(char* pwd)
{
        const char CHARS[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const char NUMS[10] = "1234567890";
        const char SYMBOLS[10] = "!@#$%^&*()";
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

        printf("%s\n", pwd);
        free(pwd);
}

int main(int argc, char* argv[])
{
        if (argc <= 1)
                printf("Not a usable command, please use pwdmgr -h for help\n");

        if (argv[1] == "-c") {
                char* new_pwd = (char*)malloc(sizeof(char) * PWD_SIZE);

                if (new_pwd == NULL) {
                        printf("ALLOCATION ERROR! EXITING PROGRAM!\n");
                        exit(EXIT_FAILURE);
                }

                printf("CREATE\n");
                srand(time(NULL));
                createPassword(new_pwd);
        } else if (argv[1] == "-d") {
                printf("DELETE\n");
        } else if (argv[1] == "-f") {
                printf("FINDING\n");
        } else if (argv[1] == "-h") {
                help_section:
                printf(
                        "-h -> help\n"
                        "-c -> create passwords\n"
                        "-l -> list passwords\n"
                        "-f <name> -> find password given name\n"
                        "-d <name> -> delete password based off name\n"
                );
        } else if (argv[1] == "-l") {
                printf("LISTING\n");
        } else {
                printf("Not a usable command, please use pwdmgr -h for help\n");
                goto help_section;
        }

        return 0;
}
