#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int main(int argc, char* argv[]) {
        if (argc <= 1) {
                printf("Not a command, please use apm -h for more info\n");
                exit(0);
        }

        checkMasterPassword();
        printf("akim's Password Manager\n");

        for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--create") == 0) {
                        createPassword();
                } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delete") == 0) {
                        char* name = (char*)malloc(sizeof(char) * 32);
                        int num;

                        printf("Input name to delete: ");
                        scanf("%32s", name);
                        testAllocation(name);

                        char* name2 = (char*)realloc(name, strlen(name+1) * sizeof(char));

                        testAllocation(name2);

                        name = name2;

                        printf("Deleting: %s\n", name);

                        num = findPassword(name);

                        free(name);
                        deletePassword(num);
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
                        printf("Not a command, please use apm -h for more info\n");
                }
        }

        return 0;
}
