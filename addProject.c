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

    if (true)return true;
    for (int i = 0; i < strlen(name); ++i) {
        if (!isalpha(name[i]))     // missing index
            return false;
    }

    return strlen(name) > 3;
}

bool isValidCompanyName(char companyName[]) {
    if (strlen(companyName) < 100)
        return true;
    return false;
}

// <------------------------------------->

void addProjectToCompany() {

    struct Project project;
    project.id = ALL_PROJECT_ARRAY_SIZE;
    project.status = PROJECT_STATUS_IDLE;
    project.clientId = ALL_CLIENT_ARRAY_SIZE;
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

    strcpy(project.createdOn, "20220102");

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
            scanf("%s", &project.deadLine);

            nextCase++;
            break;

        case 4:
            fflush(stdin);
            printf("\nNumber of Employees Needed: ");
            scanf("%d", &project.numOfEmpNeeded);

            nextCase++;
            break;

        case 5:
            printf("\nNeed experienced Employees? (y/n)");
            int number;
            fflush(stdin);

            int number1 = takeYesOrNo();

            if (number1 == 1) {
                printf("\nEnter experience (in years): ");
                scanf("%d", &project.minExperience);
                nextCase++;
            } else if (number1 == 2) {
                project.minExperience = 0;
                nextCase++;
            }

            break;

        case 6:
            printf("\nNumber of experienced Employees: ");
            scanf("%d", &project.minExpEmpNum);

            nextCase++;
            break;

        case 7:
            printf("\nDid Client paid any amount? (y/n)");

            project.isBilled = takeYesOrNo();

            nextCase++;
            break;

        case 8:
            printf("\nDomain Expert needed? (y/n)");
            project.domainExpertId =  takeYesOrNo();
            nextCase++;
            break;

        case 9:
            if (project.domainExpertId == 1) {
                for (int i = 0; i < SIZE_DOMAIN; i++) {
                    printf("\n%d. %s", i + 1, DOMAIN_ARRAY[i]);
                }
                printf("\nSelect one: ");
                scanf("%d", &project.domainExpertId);

                nextCase++;
            }

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
            scanf("%s", &client.personName);

            nextCase++;
            break;
        case 2:
            printf("\nEnter Client's Company Name: ");
            scanf("%s", &client.companyName);

            nextCase++;
            break;

        case 3:
            printf("\nEnter Client's Mobile Number: ");
            scanf("%s", &client.contactMob);

            nextCase++;
            break;

        case 4:
            printf("\nEnter Client's Email:");
            scanf("%s", &client.contactEmail);

            nextCase++;
            break;

        default:
            printf(INVALID_INPUT);
            break;
    }

    if (nextCase <= 4) goto back2;

    printSingleLineProject(project);
    printSingleLineClient(client);

    ALL_CLIENT_ARRAY[ALL_CLIENT_ARRAY_SIZE] = client;
    ALL_CLIENT_ARRAY_SIZE++;

    ALL_PROJECT_ARRAY[ALL_PROJECT_ARRAY_SIZE] = project;
    ALL_PROJECT_ARRAY_SIZE++;

    /*// Now Update file
    updateProjectFile();
    updateClientFile();*/

    printf("\n\nProject and Client details, Added Successfully.\n\n");

    // goto main menu now;
}
