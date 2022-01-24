#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

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

bool isValidName(const char s[]) {

    bool correctAlpha = true;
    for (int i = 0; i < strlen(s); ++i) {
        if (!isalpha(s[i]) && s[i] != ' ') {
            correctAlpha = false;
            break;
        }
    }

    int nameLength = strlen(s);
    bool correctLength = nameLength > 0 && nameLength < 25;
    return (correctAlpha && correctLength);
}

bool isValidDateG(char date[]) {
    SYSTEMTIME s;
    GetSystemTime(&s);
    if (strlen(date) == 8) {
        int dd, mm, yyyy;
        mm = substr(date, 2, 3);
        dd = substr(date, 0, 1);
        yyyy = substr(date, 4, 7);
        if (dd >= 1 && dd <= 31 && mm >= 1 && mm <= 12 && yyyy >= 1900) {
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
    } else return false;
}

bool isValidDesignation(int designation) {
    if (designation <= SIZE_DESIG && designation >= 1) return true;
    else return false;
}

bool isValidEmail(char mailId[]) {
    int i, p1, p2;
    p1 = p2 = 0;
    if (isalpha(mailId[0]) || isdigit(mailId[0])) {
        for (i = 0; mailId[i] != '\0'; i++) {
            if (mailId[i] == '@') p1 = i;
            else if (mailId[i] == '.' && isalpha(mailId[i - 1]) && isalpha(mailId[i + 1])) p2 = i;
        }
        if (p1 >= 1 && (p2 - p1) >= 1) return true;
        else return false;
    } else return false;
}

bool isValidMobile(char mob[]) {
    int flag = 1, i = 0;
    if (strlen(mob) == 10) {
        while (i < strlen(mob)) {
            if (!isdigit(mob[i])) {
                flag = 0;
                break;
            } else i += 1;
        }
        if (flag == 1) return true;
        else return false;
    } else return false;
}

bool isValidManagerId(int id, int totalManager) {
    if (id <= totalManager && id > 0) return true;
    else return false;
}

bool isValidDob(char dob[]) {
    int dd, mm, yyyy;
    int month[] = {31, 28, 31, 30, 31, 30, 31,
                   31, 30, 31, 30, 31};
    SYSTEMTIME s;
    GetSystemTime(&s);
    if (isValidDateG(dob)) {
        mm = substr(dob, 2, 3);
        dd = substr(dob, 0, 1);
        yyyy = substr(dob, 4, 7);
        if (dd > s.wDay) {
            s.wDay = s.wDay + month[mm - 1];
            s.wMonth = s.wMonth - 1;
        }
        if (mm > s.wMonth) {
            s.wYear = s.wYear - 1;
            s.wMonth = s.wMonth + 12;
        }
        int calculated_year = s.wYear - yyyy;

        if (calculated_year >= 18) return true;
        else return false;
    } else printf("no");
}

bool isValidPrevExperience(char dob[], int prevExp) {
    int dd, mm, yyyy;
    int month[] = {31, 28, 31, 30, 31, 30, 31,
                   31, 30, 31, 30, 31};
    SYSTEMTIME s;
    GetSystemTime(&s);
    mm = substr(dob, 2, 3);
    dd = substr(dob, 0, 1);
    yyyy = substr(dob, 4, 7);
    if (dd > s.wDay) {
        s.wDay = s.wDay + month[mm - 1];
        s.wMonth = s.wMonth - 1;
    }
    if (mm > s.wMonth) {
        s.wYear = s.wYear - 1;
        s.wMonth = s.wMonth + 12;
    }
    int calculated_year = s.wYear - yyyy;

    if (prevExp <= calculated_year - 18) return true;
    else return false;
}

bool isValidDomain(char domain) {
    if (domain > 0 && domain < SIZE_DOMAIN) return true;
    else return false;
}

bool isValidPassword(char password[]) {
    int length = strlen(password);
    return length > 3 && length < 20;
}

void addEmployeeToCompany() {

    struct Employee newEmp;

    newEmp.id = ALL_EMP_ARRAY_SIZE;
    newEmp.engagedProjects = 0;

    int nextCase = 1;
    char password[50];

    retake:
    switch (nextCase) {

        case 1:
            printf("\nEnter Name: ");
            gets(newEmp.name);

            if (isValidName(newEmp.name)) nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 2:
            printf("\nEnter Joining Date (dd/mm/yyyy): ");
            gets(newEmp.joiningDate);

            if (isValidDateG(newEmp.joiningDate)) nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 3:
            printf("\nChoose Designation");

            // print all designations
            for (int i = 0; i < SIZE_DESIG; i++) {
                printf("\n%d. %s", i + 1, DESIG_ARRAY_EMP[i]);
            }
            printf("\n");

            scanf(" %d", &newEmp.designation);
            fflush(stdin);

            if (isValidDesignation(newEmp.designation)) nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 4:
            printf("\nEnter Email: ");
            gets(newEmp.email);

            if (isValidEmail(newEmp.email)) nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 5:
            printf("\nEnter Mobile No.: ");
            gets(newEmp.mobile);

            if (isValidMobile(newEmp.mobile)) nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 6: {
            printf("\n\nChoose manager for employee\n");
            int numOfManagers = showAllManagersCustom();
            scanf("%d", &newEmp.managerId);

            if (isValidManagerId(newEmp.managerId, numOfManagers)) nextCase++;
            else printf(INVALID_INPUT);
            break;
        }

        case 7:
            printf("\nEnter Date Of Birth(dd/mm/yyyy): ");
            fflush(stdin);
            gets(newEmp.dob);

            if (isValidDob(newEmp.dob)) nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 8:
            printf("\nEnter Previous Experience (in years): ");
            scanf("%d", &newEmp.prevExperience);

            if (isValidPrevExperience(newEmp.dob, newEmp.prevExperience)) nextCase++;
            else printf(INVALID_INPUT);

            break;

        case 9: {
            printf("\nChoose Expertise in domain: ");
            for (int i = 0; i < SIZE_DOMAIN; i++)
                printf("\n%d. %s", i + 1, DOMAIN_ARRAY[i]);


            scanf("%d", &newEmp.domainExpert);

            if (isValidDomain(newEmp.domainExpert)) nextCase++;
            else printf(INVALID_INPUT);
            break;

        }

        case 10:
            if (newEmp.designation == EMP_DESIG_MANAGER || newEmp.designation == EMP_DESIG_ADMIN) {
                printf("\nEnter a password for employee account: ");
                fflush(stdin);
                gets(password);

                if (isValidPassword(password)) nextCase++;
                else printf(INVALID_INPUT);
                break;
            } else nextCase++;

        default:
            printf(INVALID_INPUT);
            break;
    }

    if (nextCase <= 10) goto retake;

    /*askAgain:
    printf("\nAre You Sure? [y/n]: ");
    char input = getchar();
    if (input != 'y' && input != 'n')goto askAgain;
    else if (input == 'y') printSingleLineEmployee(newEmp);*/

    printSingleLineEmployee(newEmp);

    return;

    // saving data into database
    ALL_EMP_ARRAY[ALL_EMP_ARRAY_SIZE++] = newEmp;
    updateEmployeeFile();

    // Adding a new row to login file
    if (newEmp.designation == EMP_DESIG_ADMIN || newEmp.designation == EMP_DESIG_MANAGER) {
        struct Login loginTemp;
        loginTemp.empId = newEmp.id;
        strcpy(loginTemp.password, "");

        loginTemp.role = newEmp.designation;

        strcpy(loginTemp.userName, newEmp.email);

        printSingleLineLogin(loginTemp);

        ALL_LOGIN_ARRAY[ALL_LOGIN_ARRAY_SIZE++] = loginTemp;
        updateLoginFile();
    }

    // call main menu


}