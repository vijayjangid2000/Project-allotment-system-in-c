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
    printf("\nGoto Menu (Enter 1)? ");
    int choice = takeInputInteger(1, 1);
    if (choice == 1) {
        return true;
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
            return;
            //showLoginDashboard();
            break;
        case 1:
            // to allot employees to project
            allotEmployeeToProject();
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 2: {
            // to edit project status

            int count = getCountProjectByStatus(PROJECT_STATUS_PROGRESS);
            if (count == 0) {
                printf("\nThere are no projects of status InPROGRESS");
            } else {
                printf("\nThis will change the project status to COMPLETE, Choose one project: \n");
                struct Project tempArray[ALL_PROJECT_ARRAY_SIZE];
                displayProjectsByProgressStatus(PROJECT_STATUS_PROGRESS, tempArray);
                int row = takeInputInteger(1, count);
                changeProjectStatusToIdle(tempArray[row - 1].id);
            }
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 3: {
            // to show employees in project
            int count = getCountProjectByStatus(PROJECT_STATUS_PROGRESS);
            if (count == 0) {
                printf("\nThere are no projects of status InPROGRESS");
            } else {

                printf("\n\nChoose one project");
                struct Project tempArray[ALL_PROJECT_ARRAY_SIZE];
                displayProjectsByProgressStatus(PROJECT_STATUS_PROGRESS, tempArray);
                int row = takeInputInteger(1, count);

                displayEmployeesForProject(tempArray[row - 1].id);
            }

            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 4: {
            // show client info for a project
            printf("\n\nChoose one project");
            struct Project tempArray[ALL_PROJECT_ARRAY_SIZE];
            displayAllProjects(tempArray);
            int row = takeInputInteger(1, getCountAllProjects());

            printf("\n Client Information for Project Id: %d", tempArray[row - 1].id);
            displayClientByProjectId(tempArray[row - 1].id);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 5: {
            // report by project status
            printf("\nChoose status: ");
            printf("\n1. Idle\n2. InProgress\n3. Completed");
            int status = takeInputInteger(1, 3);
            printf("\n");
            displayProjectsByProgressStatus(status, NULL);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 6:
            // report by employee status
            printf("\nChoose status");
            printf("\n1. Idle\n2. Busy\n");
            int status = takeInputInteger(1, 2);
            printf("\n");
            displayEmployeesByWorkStatus(status, NULL);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 7:
            // to show report for employees and projects
            displayAllProjects(NULL);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 8:
            // to display all clients
            displayAllClients();
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 9:
            // to display all admins
            displayEmployeesByDesignation(EMP_DESIG_ADMIN, NULL);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 10:
            // to display all managers
            displayEmployeesByDesignation(EMP_DESIG_MANAGER, NULL);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;

        case 11:
            // to display all employees
            displayAllEmployees();
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;

        default:
            printf(INVALID_INPUT);
            goto showOptionsAgain;
    }
}

void startApp() {
    initialLoading();
    //resetDatabase();
    //startTestingForFiles();
    showLoginDashboard();

}

void backToMenu() {
    int who = currentUser.role;
    if (who == EMP_DESIG_ADMIN) showAdminOptions();
    else if (who == EMP_DESIG_MANAGER) showManagerOptions();
}