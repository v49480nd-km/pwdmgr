#ifndef UTILS_H
#define UTILS_H

#define BUFFER 50
#define MAJOR 0
#define MINOR 3
#define PATCH 0
#define PWD_SIZE 18

int findPassword();
void checkMasterPassword();
void createPassword();
void listPasswords();
void setMasterPassword();
void storePassword(char* name, char* pwd);
void testAllocation(char* test_var);

#endif
