#ifndef UTILS_H
#define UTILS_H

#define BUFFER 50
#define MAJOR 0
#define MINOR 5
#define PATCH 0
#define PWD_SIZE 18

int findPassword(char* name);
void checkMasterPassword();
void createPassword();
void deletePassword(int line_num);
void listPasswords();
void setMasterPassword();
void storePassword(char* name, char* pwd);
void testAllocation(char* test_var);

#endif
