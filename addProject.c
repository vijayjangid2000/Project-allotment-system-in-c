#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include "aDbHelper.h"

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

bool isValidEmployeeNeeded(int numEmp) {
    if (numEmp < 100 && numEmp >= 3) {
        return true;
    }
    return false;
}

bool isValidMinimumExperience(int minExp) {
    if (minExp > 0 && minExp <= 10)
        return true;
    else
        return false;
}

bool isValidNumOfMinExperience(int numMinExp, int numEmp) {
    if (numMinExp > 0 && numMinExp <= numEmp) {
        return true;
    }
    return false;
}

bool isValidDomainExpertId(int domainExpertId) {
    if (domainExpertId > 0 && domainExpertId <= SIZE_DOMAIN) {
        return true;
    }
    return false;
}

bool isValidClientName(char name[]) {

    for (int i = 0; i < strlen(name); ++i)
        if (!isalpha(name[i]))     // missing index
            return false;

    return strlen(name) > 3;
}

bool isValidCompanyName(char companyName[]) {
    if (strlen(companyName) < 100)
        return true;
    return false;
}

bool isValidMobileNumber(char number[]) {
    bool valid1 = true;

    int i = 0;
    while (i < strlen(number)) {
        if (!isalpha(number[i])) {
            valid1 = false;
            break;
        }
        i++;
    }

    if (strlen(number) == 10 && valid1) return true;
    return false;
}

bool isValidEmailId(char mailId[]) {
    int i, p1, p2;
    p1 = p2 = 0;
    for (i = 0; mailId[i] != '\0'; i++) {
        if (mailId[i] == '@')
            p1 = i;
        else if (mailId[i] == '.')
            p2 = i;
    }
    if (p1 > 3 && (p2 - p1) > 3)
        return true;
    else
        return false;
}

// <------------------------------------->

void addProjectToCompany() {

    struct Project project;
    project.id = ALL_PROJECT_ARRAY_SIZE;
    project.status = PROJECT_STATUS_IDLE;
    project.clientId = SIZE_COLUMNS_CLIENT;
    project.managerId = 0;

    char createdDate[9];
    SYSTEMTIME s;
    GetSystemTime(&s);

    int year = s.wYear, month = s.wMonth, day = s.wDay;
    if (s.wMonth < 10) {

        sprintf(createdDate, "%d/0%d/%d", day, month, year);
    } else {
        sprintf(createdDate, "%d/%d/%d", day, month, year);

    }

    strcpy(project.createdOn, createdDate);

    int nextCase = 1;

    back1:
    switch (nextCase) {

        case 1:
            fflush(stdin);
            printf("\nEnter Project Name: ");
            gets(project.name);
            if (isValidProjectName(project.name)) { nextCase++; }
            else { printf(INVALID_INPUT); }
            break;

        case 2:
            fflush(stdin);
            printf("\nDescription: ");
            gets(project.description);
            if (isValidDescription(project.description)) nextCase++;
            else printf(INVALID_INPUT);
            break;

        case 3:
            fflush(stdin);
            printf("\nDeadline: ");
            scanf("%s", &project.deadLine);

            if(true){
                nextCase++;
                break;
            }

            if (isValidDeadLine(project.deadLine)) nextCase++;
            else printf(INVALID_INPUT);
            break;

        case 4:
            fflush(stdin);
            printf("\nHow many employees will be needed for this project?");
            scanf("%d", &project.numOfEmpNeeded);
            if (isValidEmployeeNeeded(project.numOfEmpNeeded)) nextCase++;
            else printf(INVALID_INPUT);
            break;

        case 5:
            printf("\nDo you need experienced employee in this project?");
            printf("\nEnter: 1. Yes\n       2. No: ");
            int number;
            scanf("%d", &number);
            fflush(stdin);

            if (number == 1) {
                printf("\nEnter Minimum experience that an employee must have: ");
                scanf("%d", &project.minExperience);

                if (isValidMinimumExperience(project.minExperience)) nextCase++;
                else printf(INVALID_INPUT);

            } else if (number == 2) {
                project.minExperience = 0;
                nextCase++;
            } else {
                printf(INVALID_INPUT);
            }
            break;

        case 6:
            printf("\nEnter number of Experienced employees needed in project: ");
            scanf("%d", &project.minExpEmpNum);

            if (isValidNumOfMinExperience(project.minExpEmpNum, project.numOfEmpNeeded))
                nextCase++;
            else printf(INVALID_INPUT);
            break;

        case 7:
            printf("\nDid Client paid any amount?");
            printf("\nEnter: 1. Yes\n       2. No\n");
            scanf("%d", &number);
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

        case 8:
            printf("\nDo you need Domain Expert in this project?");
            printf("\nEnter: 1. Yes\n 2. No");
            scanf("%d", &number);

            if (number == 1) {
                project.domainExpertId = -1;
                nextCase++;
            } else if (number == 2) {
                project.domainExpertId = 0;
                nextCase++;
            } else printf(INVALID_INPUT);


            break;

        case 9:
            if (project.domainExpertId != 0) {
                for (int i = 0; i < SIZE_DOMAIN; i++) {
                    printf("\n%d. %s", i + 1, DOMAIN_ARRAY[i]);
                }
                printf("\nSelect one: ");
                scanf("%d", &project.domainExpertId);
            }
            if (isValidDomainExpertId(project.domainExpertId))nextCase++;
            else printf(INVALID_INPUT);

            break;

        default:
            printf(INVALID_INPUT);
            break;
    }
    if (nextCase <= 9) goto back1;


    // TAKE CLIENT DETAILS NOW
    struct Client client;
    char email[100], name[20];

    client.projectId = project.id;
    client.clientId = ALL_CLIENT_ARRAY_SIZE;

    nextCase = 1;
    back2:
    switch (nextCase) {
        case 1:
            printf("\nEnter Client's Name: ");
            fflush(stdin);
            gets(name);

            if (isValidClientName(client.personName)) nextCase++;
            else printf(INVALID_INPUT);

            break;
        case 2:
            printf("\nEnter Client's Company Name: ");
            gets(client.companyName);

            if (isValidCompanyName(client.companyName)) nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 3:
            printf("\nEnter Client's Mobile Number: ");
            scanf("%s", &client.contactMob);

            if (isValidMobileNumber(client.contactMob))nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 4:
            printf("\nEnter Client's Email:");
            scanf("%s", &email);

            if (isValidEmailId(client.contactEmail))nextCase++;
            else printf(INVALID_INPUT);

            break;

        default:
            printf(INVALID_INPUT);
            break;
    }
    if (nextCase <= 4)goto back2;

    printSingleLineProject(project);
    printSingleLineClient(client);

    ALL_CLIENT_ARRAY[ALL_CLIENT_ARRAY_SIZE] = client;
    ALL_CLIENT_ARRAY_SIZE++;

    ALL_PROJECT_ARRAY[ALL_PROJECT_ARRAY_SIZE] = project;
    ALL_PROJECT_ARRAY_SIZE++;

    // Now Update file
    updateProjectFile();
    updateClientFile();

    printf("\n\nProject and Client details Added Successfully\n\n");

    // goto main menu now;
}
