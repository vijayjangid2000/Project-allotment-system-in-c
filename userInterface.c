#include <stdlib.h>
#include <stdio.h>
#include "databaseHelper.h"

void admin();
void manager();

void mainExit() {
    system("cls");
    printf("\n\nThanks.....\n\n");
}

// ADMIN'S WORK FUNCTIONALITY

void createNewEmployee() {
    system("cls");
    int goBack;

    printf("\n\n\t\t\tEmployee created");

    printf("\n\n\t\t\tEnter 1 to go to the menu or 0 to exit : ");
    scanf("%d", &goBack);

    if (goBack == 1) {
        admin();
    } else {
        mainExit();
    }
}

void addProject() {
    system("cls");
    int goBack;

    printf("\n\n\t\t\tproject created");

    printf("\n\n\t\t\tEnter 1 to go to the menu or 0 to exit : ");
    scanf("%d", &goBack);

    if (goBack == 1) {
        admin();
    } else {
        mainExit();
    }
}

void displayProject() {
    system("cls");
    int goBack;

    printf("\n\n\t\t\tDisplaying Project Details");

    printf("\n\n\t\t\tnEnter 1 to go to the menu or 0 to exit : ");
    scanf("%d", &goBack);

    if (goBack == 1) {
        admin();
    } else {
        mainExit();
    }
}

void displayEmployee() {
    system("cls");
    int goBack;

    printf("\n\n\t\t\tDisplaying Employee Details");

    printf("\n\n\t\t\tEnter 1 to go to the menu or 0 to exit : ");
    scanf("%d", &goBack);

    if (goBack == 1) {
        admin();
    } else {
        mainExit();
    }
}

// MANAGER FUNCTIONALITIES MENU

void displayIdleProjects() {
    system("cls");
    int goBack;

    printf("\n\n\t\t\tDisplaying Idle Projects");

    printf("\n\n\t\t\tEnter 1 to go to the menu or 0 to exit : ");
    scanf("%d", &goBack);

    if (goBack == 1) {
        manager();
    } else {
        mainExit();
    }
}

void displayIdleEmployees() {
    system("cls");
    int goBack;

    printf("\n\n\t\t\tDisplaying Idle Employees");

    printf("\n\n\t\t\tEnter 1 to go to the menu or 0 to exit : ");
    scanf("%d", &goBack);

    if (goBack == 1) {
        manager();
    } else {
        mainExit();
    }
}

void AllotEmployeesToProject() {
    system("cls");
    int goBack;

    printf("\n\n\t\t\tAllotment in progress......");

    printf("\n\n\t\t\tEnter 1 to go to the menu or 0 to exit : ");
    scanf("%d", &goBack);

    if (goBack == 1) {
        manager();
    } else {
        mainExit();
    }
}

void displayMembers2() {
    system("cls");
    int goBack;

    printf("\n\n\t\t\tDisplaying Allotment Details");

    printf("\n\n\t\t\tEnter 1 to go to the menu or 0 to exit : ");
    scanf("%d", &goBack);

    if (goBack == 1) {
        manager();
    } else {
        mainExit();
    }
}

// MENU FOR ADMIN

void admin() {
    system("cls");
    int ch;
    printf("\n\n\t\t\t-------- ADMIN PANEL --------");
    printf("\n\n\n\t\t\t1. Add Employee");
    printf("\n\t\t\t2. Add Project");
    printf("\n\t\t\t3. Display Project Details");
    printf("\n\t\t\t4. Display Employee Details");

    printf("\n\n\n\t\t\tEnter Your Choice : ");
    scanf("%d", &ch);
    printf("\n");
    switch (ch) {
        case 1:
            createNewEmployee();
            break;
        case 2:
            addProject();
            break;
        case 3:
            displayProject();
            break;
        case 4:
            displayEmployee();
            break;

        case 0:
            printf("\n\nThanks.....\n\n");
    }
}

// MENU FOR MANAGER

void manager() {
    system("cls");
    int ch;
    printf("\n\n\t\t\t-------- MANAGER PANEL --------");
    printf("\n\n\n\t\t\t1. Display Idle Projects");
    printf("\n\t\t\t2. Display Idle Employees");
    printf("\n\t\t\t3. Allot Employees To Project");
    printf("\n\t\t\t4. Display Allotment Details");

    printf("\n\n\n\t\t\ttEnter Your Choice : ");
    scanf("%d", &ch);
    printf("\n");

    switch (ch) {
        case 1:
            displayIdleProjects();
            break;
        case 2:
            displayIdleEmployees();
            break;
        case 3:
            AllotEmployeesToProject();
            break;
        case 4:
            displayMembers2();
            break;

        case 0:
            printf("\n\nThanks.....\n\n");
    }
}

// LOGIN FUNCTIONALITY FOR CHECKING ADMIN AND MANAGER

void login1() {
    int num;

    printf("\t\tLogged in\n\n");

    printf("\t\tEnter A Number : ");
    scanf("%d", &num);

    if (num == 1) {
        system("cls");
        admin();
    }

        // else
    else {
        system("cls");
        manager();
    }
}

void startUI() {
    system("color 0B");

    printf("\n\n\t\t\t\tPROJECT ALLOCATION SYSTEM");

    int ch;

    printf("\n\n\n\t\t1.Login");

    printf("\n\n\n\t\tEnter Your Choice : ");
    scanf("%d", &ch);
    switch (ch) {
        case 1:
            login1();
            break;

        case 0:
            printf("\n\nThanks.....\n\n");
    }

}
