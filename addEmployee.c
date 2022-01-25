#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include "auserInterface.h"

#include "aDbHelper.h"

void addEmployeeToCompany() {

    struct Employee newEmp;

    newEmp.id = ALL_EMP_ARRAY_SIZE + 1;
    newEmp.engagedProjects = 0;

    int nextCase = 1;
    char password[50];

    retake:
    switch (nextCase) {

        case 1:
            printf("\nEnter employee Name: ");
            takeInputString(newEmp.name, 3, 25);

            nextCase++;
            break;

        case 2:
            printf("\nEnter Joining Date(yyyyMMdd): ");
            fflush(stdin);
            takeInputString(newEmp.joiningDate, 8, 8);

            nextCase++;
            break;

        case 3:
            printf("\nChoose Designation");

            // print all designations
            for (int i = 0; i < SIZE_DESIG; i++) {
                printf("\n%d. %s", i + 1, DESIG_ARRAY_EMP[i]);
            }
            newEmp.designation = inputTakeInt(1, SIZE_DESIG);
            nextCase++;
            break;

        case 4:
            printf("\nEnter Email: ");
            takeInputString(newEmp.email, 3, 30);
            if (!isValidEmailId(newEmp.email)) break;

            nextCase++;
            break;

        case 5:
            printf("\nEnter Mobile No.: ");
            takeInputString(newEmp.mobile, 10, 10);

            nextCase++;
            break;

        case 6: {
            printf("\nEnter Manager Id");
            newEmp.managerId = inputTakeInt(1, ALL_EMP_ARRAY[ALL_EMP_ARRAY_SIZE - 1].id);

            nextCase++;
            break;
        }

        case 7:
            printf("\nEnter Date Of Birth: ");
            takeInputString(newEmp.dob, 8, 8);
            nextCase++;
            break;

        case 8:
            printf("\nEnter Experience (in years): ");
            newEmp.prevExperience = inputTakeInt(1, 20);
            nextCase++;
            break;

        case 9: {
            printf("\nChoose Expertise in domain: ");
            for (int i = 0; i < SIZE_DOMAIN; i++)
                printf("\n%d. %s", i + 1, DOMAIN_ARRAY[i]);
            newEmp.domainExpert = inputTakeInt(1, SIZE_DOMAIN);

            nextCase++;
            break;
        }

        case 10:
            if (newEmp.designation == EMP_DESIG_MANAGER || newEmp.designation == EMP_DESIG_ADMIN) {
                printf("\nCreate a password for employee account: ");
                takeInputString(password, 5, 30);
                nextCase++;
                break;
            } else nextCase++;

        default:
            printf(INVALID_INPUT);
            break;
    }

    if (nextCase <= 10) goto retake;

    //printSingleLineEmployee(newEmp);


    ALL_EMP_ARRAY[ALL_EMP_ARRAY_SIZE++] = newEmp;
    updateEmployeeFile();

    // Adding a new row to login file
    if (newEmp.designation == EMP_DESIG_ADMIN || newEmp.designation == EMP_DESIG_MANAGER) {
        struct Login loginTemp;
        loginTemp.empId = newEmp.id;
        strcpy(loginTemp.password, password);

        loginTemp.role = newEmp.designation;

        strcpy(loginTemp.userName, newEmp.email);

        //printSingleLineLogin(loginTemp);

        ALL_LOGIN_ARRAY[ALL_LOGIN_ARRAY_SIZE++] = loginTemp;
        updateLoginFile();
    }

    printf("\nSuccessful, Employee details Saved");

    // call main menu
    printf("\nGoto main menu? (y/n) ");

    if(takeYesOrNo()) backToMenu();
    else printf("\nExiting App");
}