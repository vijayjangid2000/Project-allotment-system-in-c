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
    else showManagerOptions();
}

bool gotoMenu() {
    printf("\nGoto Menu (Enter 1)? ");
    int choice = inputTakeInt(1, 1);
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
            displayAllProjects();
            int index = inputTakeInt(1, getCountAllProjects());
            printf("\nChoose new Status");
            printf("\n1. Idle\n2. InProgress\n3. Completed\n");
            int status = inputTakeInt(1, 3);
            ALL_PROJECT_ARRAY[index + 1].status = status;
            updateProjectFile();
            printf("%s", "\nProject status updated!\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 3: {
            // to show employees in project
            displayAllProjects();
            printf("\n\nChoose one project");
            int index = inputTakeInt(1, getCountAllProjects());
            int projectId = ALL_PROJECT_ARRAY[index + 1].id;

            printf("\n\nEmployees working in this project");
            displayEmployeesForProject(projectId);
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 4: {
            // show client info for a project
            displayAllProjects();
            int index = inputTakeInt(1, getCountAllProjects());
            int projectId = ALL_PROJECT_ARRAY[index + 1].id;
            printf("\n Client Information");
            displayClientByProjectId(projectId);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 5: {
            // report by project status
            printf("\nChoose status: ");
            printf("\n1. Idle\n2. InProgress\n3. Completed");
            int status = inputTakeInt(1, 3);
            printf("\n");
            displayProjectsByProgressStatus(status);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        }
        case 6:
            // report by employee status
            printf("\nChoose status");
            printf("\n1. Idle\n2. Busy\n");
            int status = inputTakeInt(1, 2);
            printf("\n");
            displayEmployeesByWorkStatus(status);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 7:
            // to show report for employees and projects
            displayAllProjects();
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
            displayEmployeesByDesignation(EMP_DESIG_ADMIN);
            printf("\n");
            if (gotoMenu()) goto showOptionsAgain;
            break;
        case 10:
            // to display all managers
            displayEmployeesByDesignation(EMP_DESIG_MANAGER);
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
    initialLoading(); // Necessary
    showLoginDashboard();
}

void backToMenu(){
    int who = currentUser.role;
    if (who == EMP_DESIG_ADMIN) showAdminOptions();
    else if (who == EMP_DESIG_MANAGER) showManagerOptions();
}