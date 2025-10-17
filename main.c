#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIST "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()"
#define PWD_SIZE 18

/* TODO
 * STORE PASSWORD WITH NAME
 * SEARCH FOR PASSWORD GIVEN NAME
 * DELETE PASSWORD GIVEN NAME
 * PROFIT
 */

void createPassword(char* pwd) {
    if (pwd == NULL) {
        printf("CHAR POINTER ERROR\n");
        exit(EXIT_FAILURE);
    }

    int rand_int;

    for (int i = 0; i < PWD_SIZE; i++) {
        rand_int = rand() % 73;
        pwd[i] = LIST[rand_int];
    }

    printf("%s\n", pwd);
    free(pwd);
}

int main() {
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
                char* new_pwd = (char*)malloc(sizeof(char) * PWD_SIZE + 1);

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
