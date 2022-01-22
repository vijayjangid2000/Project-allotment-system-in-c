#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "databaseHelper2.h"

const char INVALID_INPUT[100] = "\nInvalid Input, Enter again: ";

bool isValidName(const char s[]) {

    bool correctAlpha = true;
    for (int i = 0; i < strlen(s); ++i) {
        if (!isalpha(s[i]) && s[i] != ' ') {
            correctAlpha = false;
            break;
        }
    }

    int nameLength = strlen(s);

    if(true) return true;
    bool correctLength = nameLength > 0 && nameLength < 25;
    return (correctAlpha && correctLength);
}

bool isValidJoiningDate(char date[])
    return true;
}

bool isValidDesignation(int desig) {
    if (desig < SIZE_DESIG && desig >= 0) return true;
    else return false;
}

bool isValidEmail(char mailId[]) {
    return true;
}

bool isValidMobile(char mob[]) {
    int flag = 1, i = 0;
    while (i < strlen(mob)) {
        if (!isdigit(mob[i])) {
            flag = 0;
            break;
        } else {
            i = i + 1;
        }
    }
    if (flag == 1) return true;
    else return false;
}

bool isValidManagerId(int id, int totalManager) {
    return true;
}

bool isValidDob(char dob[]) {
    return true;
}

bool isValidPrevExperience(int prevExp) {
    return true;
}

bool isValidDomain(int domainId) {
    return true;
}

bool isValidPassword(char password[]) {

    return true;
}

void addNewEmployee() {

    struct Employee newEmp;

    int operation = 3;

    retake:
    switch (operation) {

        case 1:
            printf("\nEnter Name: ");
            gets(newEmp.name);

            if (isValidName(newEmp.name)) operation++;
            else printf(INVALID_INPUT);

            break;

        case 2:
            printf("\nEnter Joining Date (dd/mm/yyyy): ");
            gets(newEmp.joiningDate);

            if (isValidJoiningDate()) operation++;
            else printf(INVALID_INPUT);

            break;

        case 3:
            printf("\nEnter Designation");

            // print all designations
            for (int i = 0; i < SIZE_DESIG; i++) {
                printf("\n%d. %s", i + 1, DESIG_ARRAY_EMP[i]);
            }

            scanf(" %d", &newEmp.designation);
            fflush(stdin);

            if (isValidDesignation()) operation++;
            else printf(INVALID_INPUT);

            break;

        case 4:
            printf("\nEnter Email: ");
            gets(newEmp.email);

            if (isValidEmail("")) operation++;
            else printf(INVALID_INPUT);

            break;

        case 5:
            printf("\nEnter Mobile No.: ");
            gets(newEmp.mobile);

            if (isValidMobile()) operation++;
            else printf(INVALID_INPUT);

            break;

        case 6:
            printf("\nEnter Manager Id: ");
            scanf(" %d", &newEmp.managerId);
            fflush(stdin);

            // Print all managers, choose one id from it
            int numOfManagers = showManagers();
            if (isValidManagerId()) operation++;
            else printf(INVALID_INPUT);

            operation++;
            break;

        case 7:
            printf("\nEnter Date Of Birth(yyyyMMdd): ");
            gets(newEmp.dob);

            if (isValidDob()) operation++;
            else printf(INVALID_INPUT);

            break;

        case 8:
            printf("\nEnter Previous Experience (in years): ");
            scanf(" %d", &newEmp.prevExperience);
            fflush(stdin);

            if (isValidPrevExperience()) operation++;
            else printf(INVALID_INPUT);

            break;

        case 9:
            printf("\nChoose Expertise in domain: ");
            for (int i = 0; i < SIZE_DOMAIN; i++) {
                printf("\n%d- %s", i + 1, DOMAIN_ARRAY[i]);
            }
            scanf("%d", newEmp.domainExpert);
            fflush(stdin);

            if (isValidDomain()) operation++;
            else printf(INVALID_INPUT);

            break;
    }

    if (operation <= 9) goto retake;

    newEmp.id = ALL_EMP_ARRAY_SIZE++;
    newEmp.engagedProjects = 0;

    askAgain:
    printf("\nAre You Sure? [y/n]: ");
    char input = getchar();
    if (input != 'y' && input != 'n')goto askAgain;
    else if (input == 'y')printSingleLineEmployee(newEmp);

    // saving data into database
    updateEmployeeFile();

    // call main menu

}