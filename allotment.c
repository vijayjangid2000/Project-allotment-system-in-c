#include <stdio.h>
#include <stdbool.h>
#include "aDbHelper.h"
#include "auserInterface.h"

void startAllocation(int projectId) {

    // project Id
    struct Project chosenProject = getProjectById(projectId);

    int numOfEmpNeeded = chosenProject.numOfEmpNeeded;
    int numOfExperienced = chosenProject.minExpEmpNum;
    int numOfDomainNeeded = 1; // special Case
    int numOfSelectedEmployees = 0;

    int domainId = chosenProject.domainExpertId,
            experienceYear = chosenProject.minExperience;

    int ba = (int) (numOfEmpNeeded * 0.3), tester = ba,
            dev = numOfEmpNeeded - (2 * ba);

    if (isTesting) printf("\nAllotment Work: ", ba, dev, tester);

    struct Employee selectedEmployees[numOfEmpNeeded];
    int indexEmp = 0;

    bool haveExperienced = false,
            haveDomainPerson = false,
            haveRequiredEmployees = false,
            haveTechLead = false,
            haveProductOwner = false;

    // Checking for availability
    int tempNumOfEmpFree = 0, tempExperienced = 0;

    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {
        struct Employee empTemp = ALL_EMP_ARRAY[i];

        if (empTemp.engagedProjects < EMP_MAX_PROJECTS) {

            if (empTemp.designation == EMP_DESIG_WORKER) {
                tempNumOfEmpFree++;
            }

            if (!haveDomainPerson && empTemp.domainExpert == domainId) {
                haveDomainPerson = true;
            }

            if (!haveExperienced && empTemp.prevExperience >= experienceYear) {
                tempExperienced++;
                if (tempExperienced == numOfExperienced) haveExperienced = true;
            }
        }
    }

    if (tempNumOfEmpFree >= numOfEmpNeeded) haveRequiredEmployees = true;

    if (!haveRequiredEmployees) {
        printf("\nAllocation cancelled.");
        printf("\nWe don't have required number of employees for this project");
        return;
    } else if (!haveExperienced) {
        printf("\nAllocation cancelled.");
        printf("\nWe don't have experienced employees for this project");
        return;
    } else if (!haveDomainPerson) {
        printf("\nAllocation cancelled.");
        printf("\nWe don't have domain expert for this project");
        return;
    }

    haveDomainPerson = false;
    haveExperienced = false;

    // Allotting domainExpert and experienced Employees first
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {

        // DOMAIN EXPERT
        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_WORKER &&
            ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS) {

            if (!haveDomainPerson && ALL_EMP_ARRAY[i].domainExpert == domainId) {
                ALL_EMP_ARRAY[i].engagedProjects++;
                selectedEmployees[indexEmp] = ALL_EMP_ARRAY[i];
                numOfDomainNeeded--;
                numOfEmpNeeded--;
                haveDomainPerson = true;
                numOfSelectedEmployees++;

                if (!haveProductOwner) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_PRODUCT_OWNER;
                    haveProductOwner = true;
                } else if (!haveTechLead) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_TECH_LEAD;
                    haveTechLead = true;
                } else if (ba > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_BA;
                    ba--;
                } else if (tester > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_TESTER;
                    tester--;
                } else if (dev > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_DEVELOPER;
                    dev--;
                }

                indexEmp++;

                // EXPERIENCED HERE
            } else if (numOfExperienced > 0 && experienceYear <= ALL_EMP_ARRAY[i].prevExperience) {
                ALL_EMP_ARRAY[i].engagedProjects++;
                selectedEmployees[indexEmp] = ALL_EMP_ARRAY[i];
                numOfExperienced--;
                numOfEmpNeeded--;
                numOfSelectedEmployees++;
                if (numOfExperienced == 0) haveExperienced = true;

                if (!haveProductOwner) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_PRODUCT_OWNER;
                    haveProductOwner = true;
                } else if (!haveTechLead) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_TECH_LEAD;
                    haveTechLead = true;
                } else if (ba > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_BA;
                    ba--;
                } else if (tester > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_TESTER;
                    tester--;
                } else if (dev > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_DEVELOPER;
                    dev--;
                }
                indexEmp++;
            }

            if (haveExperienced && numOfExperienced == 0) break;
        }
    }

    int round = 0;
    again:
    // Selecting remaining workers
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {

        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_WORKER &&
            ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS &&
            numOfEmpNeeded > 0 && round == ALL_EMP_ARRAY[i].engagedProjects) {

            bool alreadyChosen = false;
            for (int j = 0; j < numOfSelectedEmployees; ++j) {
                if (selectedEmployees[j].id == ALL_EMP_ARRAY[i].id) {
                    alreadyChosen = true;
                    break;
                }
            }

            if (alreadyChosen) continue; // already selected then continue

            ALL_EMP_ARRAY[i].engagedProjects++;
            selectedEmployees[indexEmp] = ALL_EMP_ARRAY[i];
            numOfEmpNeeded--;
            numOfSelectedEmployees++;

            if (!haveProductOwner) {
                selectedEmployees[indexEmp].roleInProject = MEMBER_PRODUCT_OWNER;
                haveProductOwner = true;
            } else if (!haveTechLead) {
                selectedEmployees[indexEmp].roleInProject = MEMBER_TECH_LEAD;
                haveTechLead = true;
            } else if (ba > 0) {
                selectedEmployees[indexEmp].roleInProject = MEMBER_BA;
                ba--;
            } else if (tester > 0) {
                selectedEmployees[indexEmp].roleInProject = MEMBER_TESTER;
                tester--;
            } else if (dev > 0) {
                selectedEmployees[indexEmp].roleInProject = MEMBER_DEVELOPER;
                dev--;
            }

            indexEmp++;
        }
    }

    round++;
    if (round < EMP_MAX_PROJECTS) goto again;

    // update currentProject status to InProgress
    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        if (ALL_PROJECT_ARRAY[i].id == chosenProject.id) {
            ALL_PROJECT_ARRAY[i].status = PROJECT_STATUS_PROGRESS;
            break;
        }
    }

    // Now we have selected Employees, create members and add to member file
    numOfEmpNeeded = chosenProject.numOfEmpNeeded; // reassign value
    for (int i = 0; i < numOfEmpNeeded; ++i) {

        struct Member m;
        m.projectId = chosenProject.id;
        m.empId = selectedEmployees[i].id;
        m.empRole = selectedEmployees[i].roleInProject;

        ALL_MEMBER_ARRAY[ALL_MEMBER_ARRAY_SIZE++] = m;
    }

    // Now update all data in the file
    updateEmployeeFile();
    updateProjectFile();
    updateMemberFile();

    // set manager Id of project to the manager who is allocating
    ALL_PROJECT_ARRAY[projectId].managerId = currentUser.empId;

    // Show Message on console
    printf("\n\nSuccessful: We have allotted the required Employees to the project.\n");

    printf("\nAllotted Employees to project: %s", chosenProject.name);
    // print selected employees
    printColumnsEmployee();
    int numbering = 1;
    for (int i = 0; i < numOfEmpNeeded; ++i) {
        struct Employee emp1 = selectedEmployees[i];
        printSingleLineEmployee(emp1, numbering++);
    }

    // call main menu
    printf("\nGoto main menu? (y/n) ");

    if (takeYesOrNo()) backToMenu();
    else printf("\nExiting App");

}

void allotEmployeeToProject() {

    int total = getCountProjectByStatus(PROJECT_STATUS_IDLE);
    struct Project tempArray[ALL_PROJECT_ARRAY_SIZE];

    if (total == 0) {
        printf("\n There are no idle projects left.");

        // call main menu
        printf("\nGoto main menu? (y/n) ");
        if (takeYesOrNo()) backToMenu();
        else printf("\nExiting App");

        return;

    } else {
        displayProjectsByProgressStatus(PROJECT_STATUS_IDLE, tempArray);
        printf("\nPlease choose one project to allocate employees to it: ");
    }

    int row = takeInputInteger(1, total);

    startAllocation(tempArray[row - 1].id);
}