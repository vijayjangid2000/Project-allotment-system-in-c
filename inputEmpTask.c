#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "databaseHelper2.h"

int isNumericString(char str[]) {
    int flag = 1, i = 0;
    while (i < strlen(str)) {
        if (isalpha(str[i])) {
            flag = 0;
            break;
        } else {
            i = i + 1;
        }
    }
    if (flag == 1) {
        return 1;
    } else {
        return 0;
    }
};

int mailValidation(char mailId[]) {
    int i, p1, p2;
    p1 = p2 = 0;
    for (i = 0; mailId[i] != '\0'; i++) {
        if (mailId[i] == '@')
            p1 = i;
        else if (mailId[i] == '.')
            p2 = i;
    }
    if (p1 >= 1 && (p2 - p1) >= 1)
        return 1;
    else
        return 0;
}

int getSystemDate() {
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

int dateValidation(char ch[]) {
    int date[3], i = 0, dd, mm, yyyy;
    char *token;
    SYSTEMTIME s;
    GetSystemTime(&s);
    token = strtok(ch, "-");\
    while (token != NULL) {
        date[i] = atoi(token);
        i = i + 1;
        token = strtok(NULL, "-");
    }
    dd = date[2];
    mm = date[1];
    yyyy = date[0];
    if (yyyy < s.wYear)
        return 1;
        //printf("Valid Allotment date");

    else if (yyyy > s.wYear)
        return 0;
    //printf("Invalid Allotment Date");

    if (yyyy == s.wYear) {
        if (mm > s.wMonth)
            return 0;
            //printf("Valid Allotment date");
        else if (mm < s.wMonth)
            return 1;
            //printf("Invalid Allotment Date");
        else if (dd < s.wDay)
            return 1;
            //printf("Valid Allotment date");
        else if (dd > s.wDay)
            return 0;
            //printf("Invalid Allotment Date");
        else
            return 1;
        //printf("Same date");
    }
}

int nameValidation(char *buf) {
    int i;
    for (i = 0; i < strlen(buf); ++i)
        if (!isalpha(buf[i]) && buf[i] != ' ')
            return 0;
    return 1;
}

int experienceValidate(char dob[]) {
    char dobYear[5] = "0000";
    char dobMonth[3] = "00";
    char currentYear[5] = "0000";
    int exp;
    SYSTEMTIME s;
    GetSystemTime(&s);
    for (int i = 0; i < 4; i++) {
        dobYear[i] = dob[i];
    }
    for (int i = 4; i < 6; i++) {
        dobMonth[i] = dobMonth[i];
    }
    exp = (s.wYear - atoi(dobYear) - 1) * 12 + 12 - atoi(dobMonth) - 18 * 12;
    if (exp >= 0) {
        return exp / 12;
    } else {
        return -1;
    }
    return exp;
}

void addNewEmployee() {

    struct Employee newEmp;

    int operation = 1;

    retake:
    switch (operation) {

        case 1:
            printf("\nEnter Name: ");
            gets(newEmp.name);
            if (nameValidation(newEmp.name) == 1) {
                operation++;
            } else {
                printf("\nPlease enter a valid name");
            }
            break;

        case 2:
            printf("\nEnter Joining Date (yyyyMMdd): ");
            gets(newEmp.joiningDate);
            if (atoi(newEmp.joiningDate) <= getSystemDate() && strlen(newEmp.joiningDate) == 8) {
                operation++;
            } else {
                printf("Enter Valid Date");
            }
            break;

        case 3:
            printf("\nEnter Designation");
            for (int i = 0; i < 3; i++) {
                printf("\n%d- %s", i + 1, DESIG_ARRAY_EMP[i]);
            }
            scanf(" %d", &newEmp.designation);
            getchar();
            if (newEmp.designation <= 3 && newEmp.designation > 0) {
                operation++;
            } else {
                printf("\nPlease Enter A Value Between 1-3");
            }
            break;

        case 4:
            printf("\nEnter Email: ");
            gets(newEmp.email);
            if (mailValidation(newEmp.email) == 1) {
                operation++;
            } else {
                printf("Enter valid email address");
            }
            break;

        case 5:
            printf("\nEnter Mobile No.: ");
            gets(newEmp.mobile);
            if (strlen(newEmp.mobile) == 10 && isNumericString(newEmp.mobile) == 1) {
                operation++;
            } else {
                printf("Please Enter valid mobile no.");
            }
            break;

        case 6:
            printf("\nEnter Manager Id: ");
            scanf(" %d", &newEmp.managerId);
            getchar();
            // Print all managers, choose one id from it
            operation++;
            break;

        case 7:
            printf("\nEnter Date Of Birth(yyyyMMdd): ");
            gets(newEmp.dob);
            if (atoi(newEmp.dob) <= getSystemDate() && strlen(newEmp.dob) == 8 && experienceValidate(newEmp.dob) >= 0) {
                operation++;
            } else {
                printf("Enter Valid Date");
            }
            break;

        case 8:
            printf("\nEnter Previous Experience (in years): ");
            scanf(" %d", &newEmp.prevExperience);
            getchar();
            if (newEmp.prevExperience <= experienceValidate(newEmp.dob)) {
                operation++;
            } else {
                printf("\nPlease enter a valid experience");
            }
            break;

        case 9:
            printf("\nChoose Expertise in domain: ");
            for (int i = 0; i < 5; i++) {
                printf("\n%d- %s", i + 1, DOMAIN_ARRAY[i]);
            }
            scanf("%d", newEmp.domainExpert);
            operation++;
            break;
    }

    if (operation <= 9)goto retake;

    newEmp.id = ALL_EMP_ARRAY_SIZE++;
    newEmp.engagedProjects = 0;

    printf("Are You Sure?[y/n]:");
    if (getchar() == 'y') {

        printf(FORMAT_EMPLOYEE, newEmp.id, newEmp.name, newEmp.joiningDate, newEmp.designation,
               newEmp.email, newEmp.mobile, newEmp.managerId, newEmp.engagedProjects, newEmp.dob, newEmp.prevExperience,
               newEmp.domainExpert);
    }

    // update project table

}