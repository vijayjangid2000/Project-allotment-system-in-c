#include <stdio.h>
#include "aUserLogin.h"
#include "aDbHelper.h"
#include "addEmployee.h"
#include "addProject.h"
#include "allotment.h"

const char logoutMessage[100] = "\nLogout Successful :)\nExiting App.\n";

void showAdminOptions();

void showManagerOptions();

void showLoginDashboard() {
    int who = loginTask();
    if (who == EMP_DESIG_ADMIN) showAdminOptions();
    else if (who == EMP_DESIG_MANAGER) showManagerOptions();
}

bool gotoMenu() {
    printf("\n1. Goto Menu? ");
    int choice = inputTakeInt(1, 1);
    if (choice == 1) {
        printf("\nPlease enter 1: ");
    } else return gotoMenu();
}

void showAdminOptions() {

    int choice;

    takeInputAgain:
    printf("\n-------- ADMIN PANEL --------");
    printf("\n1. Add New Project");
    printf("\n2. Add New Employee");
    printf("\n0. Logout");

    printf("\n\nEnter choice: ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {

        case 0:
            //logout and exit app
            printf(logoutMessage);
            break;
        case 1:
            // to add project
            addProjectToCompany();
            break;
        case 2:
            // to add new employee
            addEmployeeToCompany();
            break;

        default:
            // if user enter wrong input
            printf(INVALID_INPUT);
            goto takeInputAgain;
    }

}

void showManagerOptions() {

    int nextCase;
    showOptionsAgain:
    printf("\n-------- MANAGER PANEL --------\n");
    printf("\n1. Allot Employees To Projects");
    printf("\n2. Edit Projects Status");
    printf("\n3. See Employees In Projects");
    printf("\n4. Show Client Information For Project");
    printf("\n5. Report By Project Status");
    printf("\n6. Report By Employee Status");
    printf("\n7. Display All Projects");
    printf("\n8. Display All Client");
    printf("\n9. Display All Admins");
    printf("\n10. Display All Managers");
    printf("\n11. Display All Employees");
    printf("\n0. Logout");

    printf("\n\nEnter Your Choice : ");
    scanf("%d", &nextCase);
    printf("\n");

    switch (nextCase) {
        case 0:
            // here when user logout
            printf(logoutMessage);
            //showLoginDashboard();
            break;
        case 1:
            // to allot employees to project
            allotEmployeeToProject();
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 2: {
            // to edit project status
            displayAllProjects();
            int index = inputTakeInt(1, getCountAllProjects());
            printf("\nChoose new Status");
            printf("1. Idle\n2. InProgress\n3. Completed\n");
            int status = inputTakeInt(1, 3);
            ALL_PROJECT_ARRAY[index].status = status;
            printf("%s", "\nProject status updated!\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 3: {
            // to show employees in project
            displayAllProjects();
            int index = inputTakeInt(1, getCountAllProjects());
            int projectId = ALL_PROJECT_ARRAY[index].id;

            displayEmployeesForProject(projectId);

            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 4: {
            // show client info for a project
            displayAllProjects();
            int index = inputTakeInt(1, getCountAllProjects());
            int projectId = ALL_PROJECT_ARRAY[index].id;
            displayClientByProjectId(projectId);
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 5: {
            // report by project status
            printf("\nChoose status: ");
            printf("\n1. Completed\n2. InProgress\n3. Completed");
            int status = inputTakeInt(1, 3);
            displayProjectsByProgressStatus(status);
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 6:
            // report by employee status
            printf("\nChoose status");
            printf("\n1. Idle\n2. Completed\n");
            int status = inputTakeInt(1, 2);
            displayEmployeesByWorkStatus(status);
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 7:
            // to show report for employees and projects
            displayAllProjects();
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 8:
            // to display all clients
            displayAllClients();
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 9:
            // to display all admins
            displayEmployeesByDesignation(EMP_DESIG_ADMIN);
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 10:
            // to display all managers
            displayEmployeesByDesignation(EMP_DESIG_MANAGER);
            if (gotoMenu()) goto showOptionsAgain;
            break;

        case 11:
            // to display all employees
            displayAllEmployees();
            if (gotoMenu()) goto showOptionsAgain;
            break;

        default:
            printf(INVALID_INPUT);
            goto showOptionsAgain;
    }
}

void startApp() {
    initialLoading(); // Necessary
    showLoginDashboard();
}