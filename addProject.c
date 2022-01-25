#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include "aDbHelper.h"
#include "auserInterface.h"

void addProjectToCompany() {

    struct Project project;
    project.id = ALL_PROJECT_ARRAY[ALL_PROJECT_ARRAY_SIZE - 2].id + 1;
    project.status = PROJECT_STATUS_IDLE;
    project.clientId = ALL_CLIENT_ARRAY_SIZE;
    project.managerId = 0;

    char createdDate[9];
    SYSTEMTIME s;
    GetSystemTime(&s);

    int year = s.wYear, month = s.wMonth, day = s.wDay;

    strcpy(project.createdOn, sprintf(createdDate, "%d|%d|%d", day, month, year));

    int nextCase = 1;

    back1:
    switch (nextCase) {

        case 1:
            fflush(stdin);
            printf("\nEnter Project Name: ");
            takeInputString(project.name, 5, 30);

            nextCase++;
            break;

        case 2:
            fflush(stdin);
            printf("\nDescription: ");
            takeInputString(project.description, 5, 100);

            nextCase++;
            break;

        case 3:
            printf("\nDeadline (yyyyMMdd): ");
            takeInputString(project.deadLine, 8, 8);

            nextCase++;
            break;

        case 4:
            fflush(stdin);
            printf("\nNumber of Employees Needed: ");
            project.numOfEmpNeeded = inputTakeInt(3, 100);
            nextCase++;
            break;

        case 5:
            printf("\nNeed experienced Employees? (y/n) ");
            int temp = takeYesOrNo();

            if (temp == 1) {
                printf("\nEnter experience (in years): ");
                project.minExperience = inputTakeInt(1, 30);

                nextCase++;
            } else if (temp == 2) {
                project.minExperience = 0;
                nextCase++;
            }

            break;

        case 6:
            printf("\nNumber of experienced Employees: ");
            project.minExpEmpNum = inputTakeInt(1, project.numOfEmpNeeded);

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
                project.domainExpertId = inputTakeInt(1, SIZE_DOMAIN);

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
    client.clientId = ALL_CLIENT_ARRAY[ALL_CLIENT_ARRAY_SIZE - 1].clientId + 1;

    nextCase = 1;
    back2:
    switch (nextCase) {
        case 1:
            printf("\nEnter Client's Name: ");
            takeInputString(client.personName, 5, 30);

            nextCase++;
            break;
        case 2:
            printf("\nEnter Client's Company Name: ");
            takeInputString(client.companyName, 3, 30);

            nextCase++;
            break;

        case 3:
            printf("\nEnter Client's Mobile Number: ");
            takeInputString(client.contactMob, 10, 10);

            nextCase++;
            break;

        case 4:

            printf("\nEnter Client's Email:");
            takeInputString(client.contactEmail, 3, 30);

            if (!isValidEmailId(client.contactEmail)) break;
            else nextCase++;
            break;

        default:
            printf(INVALID_INPUT);
            break;
    }

    if (nextCase <= 4) goto back2;

    // printSingleLineProject(project);
    // printSingleLineClient(client);

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
