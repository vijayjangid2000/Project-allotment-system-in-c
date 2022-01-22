#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include "databaseHelper2.h"

const char INVALID_INPUT[100] = "\nInvalid Input, Enter again: ";

bool isValidProjectName(char name[]) {
    if (strlen(name) <= 100 && strlen(name) != 0) {
        return true;
    }
    return false;
}

bool isValidDeadLine(char date[]) {
    char *pch;
    int month = 0, day = 0, year = 0;
    pch = strtok(date, "/");
    while (pch != NULL) {
        int num = atoi(pch);
        if (day == 0) day = num;
        else if (month == 0) month = num;
        else if (year == 0) year = num;
        pch = strtok(NULL, "/");
    }
    if ((month >= 1 && month <= 12) && (year >= 2022 && year <= 2022 + 50)) {
        if (month % 2 == 0 && month != 2) {
            if (month < 7) {
                if (day >= 1 && day <= 30) {
                    return true;
                }
            } else {
                if (day >= 1 && day <= 31) {
                    return true;
                }
            }
        } else if (month == 2) {
            if (day >= 1 && day <= 28) {
                return true;
            }
        } else if (month % 2 != 0) {
            if (month <= 7) {
                if (day >= 1 && day <= 31) {
                    return true;
                }
            } else {
                if (day >= 1 && day <= 30) {
                    return true;
                }
            }
        } else {
            return false;
        }

    }
    // dd/mm/yyyy
    return false;
}

bool isValidDescription(char description[]) {
    if (strlen(description) < 200 && strlen(description) > 1) {
        return true;
    }
    return false;
}

bool isValidEmployeeNeeded() {

    return true;
}

bool isValidMinimumExperience() {

    return true;
}

bool isValidNumOfMinExperience() {

    return true;
}

bool isValidBilled(int input){

}

bool isValidDomainExpertId(int domainExpertId) {
    if (domainExpertId >= 1 && domainExpertId <= 5) {
        return true;
    }
    return false;
}

bool isValidClientName() {

    return true;
}

bool isValidCompanyName() {

    return true;
}

bool isValidMobileNumber() {

    return true;
}

// <------------------------------------->

void addProjectToCompany() {

    int number, deadline, created;

    struct Project project;

    project.id = ALL_PROJECT_ARRAY_SIZE;
    project.status = PROJECT_STATUS_IDLE;
    project.managerId = -1;

    int nextCase = 1;

    back1:
    switch (nextCase) {

        case 1:
            fflush(stdin);
            printf("\nEnter Project Name: ");
            gets(project.name);
            nextCase++;
            break;

        case 2:
            fflush(stdin);
            printf("\nDescription: ");
            gets(project.description);
            nextCase++;
            break;

        case 3:
            fflush(stdin);
            printf("\nDeadline: ");
            scanf("%d", &deadline);
            if (created < deadline) {
                char s1[10];
                sprintf(s1, "%d", deadline);
                strcpy(project.deadLine, s1);
                nextCase++;
            } else {
                printf("\nInvalid Date. Enter again: ");
            }

            break;

        case 4:
            fflush(stdin);
            printf("\nHow many employees will be needed for this project?");
            scanf("%d", &project.numOfEmpNeeded);
            nextCase++;
            break;

        case 5:
            fflush(stdin);
            printf("\nDo you need experienced employee in this project?");
            printf("\nEnter: 1 for Yes\n       2 for No: ");
            scanf("%d", &number);
            fflush(stdin);

            if (number == 1) {
                printf("\nEnter Minimum experience that an employee must have: ");
                scanf("%d", &project.minExperience);
                // add validation

                fflush(stdin);
                printf("\nEnter number of Experienced employees needed in project: ");
                scanf("%d", &project.minExpEmpNum);

                if (project.numOfEmpNeeded >= project.minExpEmpNum) {
                    project.minExpEmpNum = project.minExpEmpNum;
                    nextCase++;
                } else printf("\nInvalid Input, Number greater than total employee in project. \nEnter again: ");
            } else {
                project.minExperience = 0;
                project.minExpEmpNum = 0;
            }
            break;

        case 6:
            fflush(stdin);
            printf("\nDo Client paid for project Development?");
            printf("\nEnter: 1. Yes\n       2. No\n");
            scanf("%d", &number);
            number = 1;
            if (number == 1) {
                project.isBilled = PROJECT_BILLED;
                nextCase++;
            } else if (number == 2) {
                project.isBilled = PROJECT_NOT_BILLED;
                nextCase++;
            } else {
                printf("\n Invalid Input");
            }
            break;

        case 7:

            fflush(stdin);
            printf("\nDo you need Domain Expert in this project?");
            printf("\nEnter: 1. Yes\n 2. No");
            scanf("%d", &number);

            if (number == 1) {
                project.domainExpertId = 1; // giving value other than zero
                nextCase++;
            } else if (number == 2) {
                project.domainExpertId = 0;
                nextCase++;
            } else {
                printf("\nInvalid Input");
            }
            break;

        case 8:
            if (project.domainExpertId != 0) {
                for (int i = 0; i < 5; i++) {
                    printf("\n%d. %s", i + 1, DOMAIN_ARRAY[i]);
                }
                printf("\nSelect one: ");
                scanf("%d", &project.domainExpertId);
            }
            nextCase++;
            break;
    }
    if (nextCase <= 8) goto back1;

    project.clientId = SIZE_COLUMNS_CLIENT;
    printSingleLineProject(project);

    struct Client client;
    char email[100], name[20];

    client.projectId = project.id;
    client.clientId = ALL_CLIENT_ARRAY_SIZE;

    nextCase = 1;

    again:
    switch (nextCase) {
        case 1:
            printf("\nEnter Client's Name: ");
            gets(name);

            if (isValidClientName(client.personName)) nextCase++;
            else printf(INVALID_INPUT);
            break;

        case 2:
            printf("\nEnter Client's Company Name: ");
            gets(client.companyName);
            if (strlen(client.companyName) > 2) nextCase++;
            else printf("\nInvalid Input.");
            break;

        case 3:
            printf("\nEnter Client's Mobile Number: ");
            scanf("%s", &client.contactMob);
            if (strlen(client.contactMob) == 10) {
                printf(" ");
                nextCase++;
            } else printf("\nInvalid Input");
            break;

        case 4:
            printf("\nEnter Client's Email:");
            scanf("%s", &email);
            if (true) {
                strcpy(client.contactEmail, email);
                nextCase++;
            } else {
                printf("(Invalid Email)");
                printf("\nEmail:");
                scanf("%s", &email);

            }
            break;
    }
    if (nextCase <= 4)goto back1;

    printSingleLineClient(client);

    printf("Project Added Successfully");

    ALL_CLIENT_ARRAY[ALL_CLIENT_ARRAY_SIZE] = client;
    ALL_CLIENT_ARRAY_SIZE++;

    ALL_PROJECT_ARRAY[ALL_PROJECT_ARRAY_SIZE] = project;
    ALL_PROJECT_ARRAY_SIZE++;

    // Now Update file
    updateProjectFile();
    updateClientFile();
}
