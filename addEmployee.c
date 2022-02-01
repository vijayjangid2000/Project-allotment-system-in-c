#include<stdio.h>
#include<windows.h>
#include<string.h>
#include "auserInterface.h"
#include "aDbHelper.h"

int substr(char date[], int start, int end) {
    char ch[end - start + 1];
    int j = 0;
    for (int i = start; i <= end; i++) {
        ch[j] = date[i];
        j = j + 1;
    }
    return atoi(ch);
}

bool isValidDate(char date[]) {
    int dd, mm, yyyy;
    bool flag = false;
    int month[] = {31, 28, 31, 30, 31, 30, 31,
                   31, 30, 31, 30, 31};
    if (strlen(date) == 8) {
        mm = substr(date, 4, 5);
        dd = substr(date, 6, 7);
        yyyy = substr(date, 0, 3);
        if (mm >= 1 && mm <= 12 && yyyy >= 1900) {
            if (mm == 2) {
                if (((yyyy % 4 == 0) && (yyyy % 100 != 0)) || (yyyy % 400 == 0)) {
                    if (dd >= 1 && dd <= month[mm - 1] + 1) flag = true;
                } else {
                    if (dd >= 1 && dd <= month[mm - 1]) flag = true;
                }
            } else {
                if (dd >= 1 && dd <= month[mm - 1]) flag = true;
            }
        }
    }
    return flag;
}

bool isValidJoiningDate(char date[]) {
    int mm, dd, yyyy;
    SYSTEMTIME s;
    GetSystemTime(&s);
    if (isValidDate(date)) {
        mm = substr(date, 4, 5);
        dd = substr(date, 6, 7);
        yyyy = substr(date, 0, 3);
        if (yyyy < s.wYear) return true;
        else if (yyyy > s.wYear) return false;
        if (yyyy == s.wYear) {
            if (mm > s.wMonth) return false;
            else if (mm < s.wMonth) return true;
            else if (dd < s.wDay) return true;
            else if (dd > s.wDay) return false;
            else return true;
        }
    } else return false;
}

int helperDoB(char date[]) {
    int dd, mm, yyyy;
    int month[] = {31, 28, 31, 30, 31, 30, 31,
                   31, 30, 31, 30, 31};
    SYSTEMTIME s;
    GetSystemTime(&s);
    mm = substr(date, 4, 5);
    dd = substr(date, 6, 7);
    yyyy = substr(date, 0, 3);
    if (dd > s.wDay) {
        s.wDay = s.wDay + month[mm - 1];
        s.wMonth = s.wMonth - 1;
    }
    if (mm > s.wMonth) {
        s.wYear = s.wYear - 1;
        s.wMonth = s.wMonth + 12;
    }

    int calculated_year = s.wYear - yyyy;

    return calculated_year;
}

bool isValidPrevExperience(char dob[], int prevExp) {
    if (prevExp <= helperDoB(dob) - 18) return true;
    else return false;
}

bool isValidEmail(char mailId[]) {
    int i, p1, p2;
    p1 = p2 = 0;
    if (isalpha(mailId[0]) || isdigit(mailId[0])) {
        for (i = 0; mailId[i] != '\0'; i++) {
            if (!isalnum(mailId[i]) && mailId[i] != '@' && mailId[i] != '.') {
                p1 = p2 = 0;
                break;
            } else {
                if (mailId[i] == '@') {
                    if (p1 == 0) p1 = i;
                    else p1 = 0;
                } else if (mailId[i] == '.') {
                    if (p2 == 0) {
                        if (isalpha(mailId[i - 1]) && isalpha(mailId[i + 1])) p2 = i;
                    } else p2 = 0;
                }
            }
        }
        if (p1 >= 1 && (p2 - p1) >= 1) return true;
        else return false;
    } else return false;
}

bool isValidDeadLine(char deadLine[]) {
    if (isValidJoiningDate(deadLine)) return false; else return true;
}

void addEmployeeToCompany() {

    struct Employee newEmp;

    newEmp.id = getIdOfEmployeeTable();
    newEmp.engagedProjects = 0;

    int nextCase = 1;
    char tempPassword[50];

    retake:
    switch (nextCase) {

        case 1:
            printf("\nEnter employee Name: ");
            takeInputString(newEmp.name, 3, 35);
            nextCase++;
            break;

        case 2:
            printf("\nEnter Joining Date(yyyyMMdd): ");
            takeInputString(newEmp.joiningDate, 8, 8);

            if (isValidJoiningDate(newEmp.joiningDate)) nextCase++;
            break;

        case 3:
            printf("\nChoose Designation");

            // print all designations
            for (int i = 0; i < SIZE_DESIG; i++) {
                printf("\n%d. %s", i + 1, DESIG_ARRAY_EMP[i]);
            }
            newEmp.designation = takeInputInteger(1, SIZE_DESIG);

            nextCase++;
            break;

        case 4:
            printf("\nEnter Email: ");
            takeInputString(newEmp.email, 3, 30);
            if (!isValidEmail(newEmp.email)) break;
            nextCase++;
            break;

        case 5:
            printf("\nEnter Mobile No.: ");
            takeInputString(newEmp.mobile, 10, 10);
            nextCase++;
            break;

        case 6: {
            if (newEmp.designation != EMP_DESIG_WORKER) {
                newEmp.managerId = 0;
                break;
            }

            printf("\n\nChoose Manager for Employee");
            struct Employee tempArray[ALL_EMP_ARRAY_SIZE];
            displayEmployeesByDesignation(EMP_DESIG_MANAGER, tempArray);
            int row = takeInputInteger(1, getCountAllProjects());

            newEmp.managerId = tempArray[row - 1].id;
            nextCase++;
            break;
        }

        case 7:
            printf("\nEnter Date Of Birth: ");
            takeInputString(newEmp.dob, 8, 8);
            if (isValidDate(newEmp.dob)) nextCase++;
            else printf("\nInvalid DOB");
            break;


        case 8:
            printf("\nEnter Experience (in years): ");
            newEmp.prevExperience = takeInputInteger(0, 35);
            if (isValidPrevExperience(newEmp.dob, newEmp.prevExperience));
            else printf("\nInvalid Previous Experience");
            nextCase++;
            break;

        case 9: {
            printf("\nChoose Expertise in domain: ");
            for (int i = 0; i < SIZE_DOMAIN; i++)
                printf("\n%d. %s", i + 1, DOMAIN_ARRAY[i]);
            newEmp.domainExpert = takeInputInteger(1, SIZE_DOMAIN);

            nextCase++;
            break;
        }

        case 10:
            if (newEmp.designation == EMP_DESIG_MANAGER || newEmp.designation == EMP_DESIG_ADMIN) {
                printf("\nCreate a password for employee account: ");
                takeInputString(tempPassword, 5, 30);
                nextCase++;
                break;
            } else nextCase++;

        default:
            break;
    }

    if (nextCase <= 10) goto retake;

    if (isTesting) printSingleLineEmployee(newEmp,1);


    ALL_EMP_ARRAY[ALL_EMP_ARRAY_SIZE++] = newEmp;
    updateEmployeeFile();

    // Adding a new row to login file
    if (newEmp.designation == EMP_DESIG_ADMIN || newEmp.designation == EMP_DESIG_MANAGER) {
        struct Login loginTemp;
        loginTemp.empId = newEmp.id;
        strcpy(loginTemp.password, tempPassword);

        loginTemp.role = newEmp.designation;

        strcpy(loginTemp.userName, newEmp.email);

        if (isTesting) printSingleLineLogin(loginTemp,1);

        ALL_LOGIN_ARRAY[ALL_LOGIN_ARRAY_SIZE++] = loginTemp;
        updateLoginFile();
    }

    printf("\nSuccessful, Employee details Saved.");

    // call main menu
    printf("\nGoto main menu? (y/n) ");

    if (takeYesOrNo()) backToMenu();
    else printf("\nExiting App");
}