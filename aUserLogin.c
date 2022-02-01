#include<stdio.h>
#include<string.h>
#include "aDbHelper.h"

void encrypt(char password[]) {

}

void decrypt(char password[]) {

}

/*int shortcut() {
    strcpy(currentUser.userName, "ajay@gmail.com");
    currentUser.role = EMP_DESIG_ADMIN;
    strcpy(currentUser.password, "ajay123");
    currentUser.empId = 4;
    return currentUser.role;
}*/

int loginTask() {

    printf("\nWelcome to Appcino\n");
    struct Login loggedInUser;

    char userName[105], password[105];

    takeInputAgain:
    printf("\nEnter Username: ");
    again1:
    fflush(stdin);
    gets(userName);
    if (strlen(userName) > 90 || strlen(userName) < 1) {
        printf("\nEnter valid username: ");
        goto again1;
    }

    printf("Enter Password: ");
    again2:
    fflush(stdin);
    gets(password);
    if (strlen(password) > 100 || strlen(password) < 1) {
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
    printf("\nWelcome, %s!\n\n", emp.name);

    currentUser = loggedInUser;

    return loggedInUser.role;
}

