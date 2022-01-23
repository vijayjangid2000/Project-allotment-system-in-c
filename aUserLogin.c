#include<stdio.h>
#include<string.h>
#include "aDbHelper.h"

void encrypt(char password[]) {
    return;
    int key = 0xFACA;
    unsigned int i;
    for (i = 0; i < strlen(password); ++i) {
        password[i] = password[i] - key;
    }
}

void decrypt(char password[]) {
    return;
    int key = 0xFACA;
    unsigned int i;
    for (i = 0; i < strlen(password); ++i) {
        password[i] = password[i] + key;
    }
}

int loginTask() {

    printf("\nWelcome to Appcino\n\n Please Enter Account Details\n\n");
    struct Login loggedInUser;

    char userName[100], password[100];

    takeInputAgain:
    printf("\nEnter Username: ");
    again1:
    fflush(stdin);
    gets(userName);
    if (strlen(userName) > 90 || strlen(userName) < 1) {
        printf("\nEnter valid username: ");
        goto again1;
    }

    printf("\nEnter Password: ");
    again2:
    fflush(stdin);
    gets(password);
    if (strlen(password) > 90 || strlen(password) < 1) {
        printf("\nEnter valid password: ");
        goto again2;
    }

    bool isUserFound = false;
    encrypt(password);

    for (int i = 0; i < ALL_LOGIN_ARRAY_SIZE; ++i) {

        struct Login currentRow = ALL_LOGIN_ARRAY[i];
        // check for username
        if (strcmp(userName, currentRow.userName) == 0) {
            strcpy(loggedInUser.userName, userName);
            // check for password now
            char tempPass[100];
            strcpy(tempPass, currentRow.password);
            decrypt(tempPass);
            if (strcmp(password, tempPass) == 0) {
                isUserFound = true;
                strcpy(loggedInUser.password, tempPass);
                // save other data too
                loggedInUser.empId = currentRow.empId;
                loggedInUser.role = currentRow.role;
                break;
            }
        }
    }

    if (!isUserFound) {
        printf("\nEnter correct username and password.");
        // printf("\nIncorrect Password, Please enter again: ");
        goto takeInputAgain;
    }

    struct Employee emp = getEmployeeById(loggedInUser.empId);
    printf("\nWelcome Back %s", emp.name);

    if (loggedInUser.role == EMP_DESIG_ADMIN) return EMP_DESIG_ADMIN;
    if (loggedInUser.role == EMP_DESIG_MANAGER) return EMP_DESIG_MANAGER;

}



