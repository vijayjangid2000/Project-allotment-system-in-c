#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include "databaseHelper.h"

int validate(char *buf) {
    int i;
    for (i = 0; i < strlen(buf); ++i)
        if (!isalpha(buf[i]) && buf[i] != ' ')   // missing index
            return 0;
    return 1;
}

bool isEmailValidB(char mailId[]) {
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

int getSystemDateB() {
    char str[100];
    int result = 0;
    SYSTEMTIME s;
    GetSystemTime(&s);
    if (s.wMonth < 10) {
        int i = s.wYear, j = s.wMonth, k = s.wDay;
        sprintf(str, "%d0%d%d", i, j, k);
        result = strtol(str, NULL, 10);

    } else {
        int i = s.wYear, j = s.wMonth, k = s.wDay;
        sprintf(str, "%d%d%d", i, j, k);
        result = strtol(str, NULL, 10);
    }
    return result;
}

// <------------------------------------->

void addClient(int projectId) {

    struct Client client;
    char email[100], name[20];

    client.projectId = projectId;

    client.clientId = ALL_CLIENT_ARRAY_SIZE;

    int operation = 1;
    retake:
    switch (operation) {
        case 1:
            printf("\nEnter Client's Name: ");
            gets(name);

            if (validate(name) == 1) {
                strcpy(client.personName, name);
                operation++;
            } else
                printf("\nInvalid Input.");
            break;

        case 2:
            printf("\nEnter Client's Company Name: ");
            gets(client.companyName);
            if (strlen(client.companyName) > 2) operation++;
            else printf("\nInvalid Input.");
            break;

        case 3:
            printf("\nEnter Client's Mobile Number: ");
            scanf("%s", &client.contactMob);
            if (strlen(client.contactMob) == 10 /*&& isNumericString(client.contactMob) == 1*/) {
                printf(" ");
                operation++;
            } else printf("\nInvalid Input");
            break;

        case 4:
            printf("\nEnter Client's Email:");
            scanf("%s", &email);
            if (isEmailValidB(email)) {
                strcpy(client.contactEmail, email);
                operation++;
            } else {
                printf("(Invalid Email)");
                printf("\nEmail:");
                scanf("%s", &email);

            }
            break;
    }
    if (operation <= 4)goto retake;
    printSingleLineClient(client);

    ALL_CLIENT_ARRAY[ALL_CLIENT_ARRAY_SIZE] = client;
    ALL_CLIENT_ARRAY_SIZE++;
}

void addProjectToCompany() {
    int deadline, created;
    int number;

    struct Project project;

    project.id = ALL_PROJECT_ARRAY_SIZE;

    project.status = PROJECT_STATUS_IDLE;

    project.managerId = -1;

    fflush(stdin);
    created = getSystemDateB();
    char s[100];
    sprintf(s, "%d", created);
    strcpy(project.createdOn, s);

    int operation = 1;
    retake:
    switch (operation) {

        case 1:
            fflush(stdin);
            printf("\nEnter Project Name: ");
            gets(project.name);
            operation++;
            break;

        case 2:
            fflush(stdin);
            printf("\nDescription: ");
            gets(project.description);
            operation++;
            break;

        case 3:
            fflush(stdin);
            printf("\nDeadline: ");
            scanf("%d", &deadline);
            if (created < deadline) {
                char s1[10];
                sprintf(s1, "%d", deadline);
                strcpy(project.deadLine, s1);
                operation++;
            } else {
                printf("\nInvalid Date. Enter again: ");
            }

            break;

        case 4:
            fflush(stdin);
            printf("\nHow many employees will be needed for this project?");
            scanf("%d", &project.numOfEmpNeeded);
            operation++;
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
                    operation++;
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
            if (number == 1) {
                project.isBilled = PROJECT_BILLED;
            } else if (number == 2) {
                project.isBilled = PROJECT_NOT_BILLED;
            } else {
                printf("\n Invalid Input");
            }
            break;

        case 7:

            fflush(stdin);
            printf("\nDo you need Domain Expert in this project?");
            printf("\nEnter: 1. Yes\n 2. No");
            fflush(stdin);
            scanf("%d", &number);
            fflush(stdin);

            if (number == 1) {
                project.domainExpertId = 1; // giving value other than zero
                operation++;
            } else if (number == 2) {
                project.domainExpertId = 0;
                operation++;
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
                scanf("%d", project.domainExpertId);
            }
            operation++;
            break;
    }
    if (operation <= 8) goto retake;

    project.clientId = SIZE_COLUMNS_CLIENT;
    printSingleLineProject(project);

    addClient(project.id);

    ALL_PROJECT_ARRAY[ALL_PROJECT_ARRAY_SIZE] = project;
    ALL_PROJECT_ARRAY_SIZE++;

    printf("Project Added Successfully");

}
