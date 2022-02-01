#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include "aDbHelper.h"
#include "auserInterface.h"
#include "addEmployee.h"

void addProjectToCompany() {

    struct Project project;
    project.id = getIdOfProjectTable();
    project.status = PROJECT_STATUS_IDLE;
    project.clientId = ALL_CLIENT_ARRAY_SIZE;
    project.managerId = 0;

    char createdDate[9];
    SYSTEMTIME s;
    GetSystemTime(&s);
    int year = s.wYear, month = s.wMonth, day = s.wDay;
    sprintf(createdDate, "%d%02d%02d", year, month, day);
    printf("%s",createdDate);

    strcpy(project.createdOn, createdDate);

    int nextCase = 1;

    back1:
    switch (nextCase) {

        case 1:
            printf("\nEnter Project Name: ");
            takeInputString(project.name, 1, 30);

            nextCase++;
            break;

        case 2:
            printf("\nDescription: ");
            takeInputString(project.description, 5, 100);

            nextCase++;
            break;

        case 3:
            printf("\nDeadline (yyyyMMdd): ");
            takeInputString(project.deadLine, 8, 8);

            if (isValidDeadLine(project.deadLine))nextCase++;
            break;

        case 4:
            fflush(stdin);
            printf("\nNumber of Employees Needed: ");
            project.numOfEmpNeeded = takeInputInteger(3, 50);
            nextCase++;
            break;

        case 5:
            printf("\nNeed experienced Employees? (y/n) ");
            int temp = takeYesOrNo();

            if (temp == 1) {
                printf("\nEnter experience (in years): ");
                project.minExperience = takeInputInteger(1, 35);

                nextCase++;
            } else if (temp == 0) {
                project.minExperience = 0;
                nextCase++;
            }

            break;

        case 6:
            printf("\nNumber of experienced Employees: ");
            project.minExpEmpNum = takeInputInteger(1, project.numOfEmpNeeded);

            nextCase++;
            break;

        case 7:
            printf("\nDid Client paid any amount? (y/n) ");
            project.isBilled = takeYesOrNo();

            nextCase++;
            break;

        case 8:
            printf("\nDomain Expert needed? (y/n) ");
            project.domainExpertId = takeYesOrNo();
            nextCase++;
            break;

        case 9:
            if (project.domainExpertId == 1) {
                for (int i = 0; i < SIZE_DOMAIN; i++) {
                    printf("\n%d. %s", i + 1, DOMAIN_ARRAY[i]);
                }
                printf("\nSelect one from list.");
                project.domainExpertId = takeInputInteger(1, SIZE_DOMAIN);

                nextCase++;
            }

            break;

        default:
            break;
    }
    if (nextCase <= 9) goto back1;


    // TAKE CLIENT DETAILS NOW
    struct Client client;
    char email[100], name[20];

    client.projectId = project.id;
    client.clientId = ALL_CLIENT_ARRAY[ALL_CLIENT_ARRAY_SIZE - 1].clientId + 1;

    nextCase = 1;
    back2:
    switch (nextCase) {
        case 1:
            printf("\nEnter Client's Name: ");
            takeInputString(client.personName, 2, 30);

            nextCase++;
            break;
        case 2:
            printf("\nEnter Client's Company Name: ");
            takeInputString(client.companyName, 2, 40);

            nextCase++;
            break;

        case 3:
            printf("\nEnter Client's Mobile Number: ");
            takeInputString(client.contactMob, 10, 10);

            nextCase++;
            break;

        case 4:

            printf("\nEnter Client's Email:");
            takeInputString(client.contactEmail, 5, 30);

            if (!isValidEmail(client.contactEmail)) break;
            else nextCase++;
            break;

        default:
            printf(INVALID_INPUT);
            break;
    }

    if (nextCase <= 4) goto back2;

    if (isTesting) {
        printSingleLineProject(project,1);
        printSingleLineClient(client,1);
    }

    ALL_CLIENT_ARRAY[ALL_CLIENT_ARRAY_SIZE] = client;
    ALL_CLIENT_ARRAY_SIZE++;

    ALL_PROJECT_ARRAY[ALL_PROJECT_ARRAY_SIZE] = project;
    ALL_PROJECT_ARRAY_SIZE++;

    // Now Update file
    updateProjectFile();
    updateClientFile();

    printf("\n\nNew Project and Client Added Successfully.\n\n");

    // call main menu
    printf("\nGoto main menu? (y/n) ");

    if (takeYesOrNo()) backToMenu();
    else printf("\nExiting App");
}
