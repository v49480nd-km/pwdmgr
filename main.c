#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PWD_SIZE 18

/* TODO
 * STORE PASSWORD WITH NAME
 * LIST PASSWORDS
 * SEARCH FOR PASSWORD GIVEN NAME
 * DELETE PASSWORD GIVEN NAME
 * PROFIT
 */

void createPassword(char* pwd)
{
        const char[52] CHARS "abcdefghijklmnopwqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const char[10] NUMS "1234567890";
        const char[10] SYMBOLS "!@#$%^&*()";
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

int main()
{
        int attempts = 5;
        int option;

        option_loop:

        printf(
                "PWDMGR\n\n"
                "[1] Create\n"
                "[2] Find\n"
                "[3] Delete\n"
                "[4] Exit\n\n"
                ">>> "
        );

        while (!option || option <= 0 || option > 4) {
                scanf("%d", &option);

                switch (option) {
                case 1:
                        char* new_pwd = (char*)malloc(sizeof(char) * PWD_SIZE);

                        if (new_pwd == NULL) {
                                printf("ALLOCATION ERROR! EXITING PROGRAM!\n");
                                exit(EXIT_FAILURE);
                        }

                        printf("CREATE\n");
                        srand(time(NULL));
                        createPassword(new_pwd);

                        option = 0;

                        goto option_loop;
                case 2:
                        printf("FIND\n");

                        option = 0;

                        goto option_loop;
                case 3:
                        printf("DELETE\n");

                        option = 0;

                        goto option_loop;
                case 4:
                        printf("EXITING...\n");
                        exit(0);
                default:
                        printf("Please try again>>> ");
                        break;
                }
        }


        return 0;
}
