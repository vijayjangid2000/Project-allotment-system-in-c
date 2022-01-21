#include<stdio.h>
#include<string.h>
#include "Utility.h"

int loginTask() {

    struct Login loggedInUser;

    char userName[100], password[100];

    takeInputAgain:
    printf("\nEnter Username: ");
    again1:
    gets(userName);
    if (strlen(userName) > 90 || strlen(userName) < 1) {
        printf("\nEnter valid username: ");
        goto again1;
    }

    printf("\nEnter Password: ");
    again2:
    gets(password);
    if (strlen(password) > 90 || strlen(password) < 1) {
        printf("\nEnter valid password: ");
        goto again2;
    }

    bool isUserFound = false;

    for (int i = 0; i < ALL_LOGIN_ARRAY_SIZE; ++i) {

        struct Login currentLogin = ALL_LOGIN_ARRAY[i];
        // check for username
        if (strcmp(userName, currentLogin.userName) == 0) {
            strcpy(loggedInUser.userName, userName);
            // check for password now
            if (strcmp(password, currentLogin.password) == 0) {
                isUserFound = true;
                strcpy(loggedInUser.password, password);
                // save other data too
                loggedInUser.empId = currentLogin.empId;
                loggedInUser.role = currentLogin.role;
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

    if (loggedInUser.role == LOGIN_ROLE_ADMIN) return LOGIN_ROLE_ADMIN;
    if (loggedInUser.role == LOGIN_ROLE_MANAGER) return LOGIN_ROLE_MANAGER;

}



