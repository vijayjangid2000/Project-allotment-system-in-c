#include <stdio.h>
#include <stdbool.h>
#include "databaseHelper.h"

void startProcess(struct Project chosenProject) {

    int numOfEmpNeeded = chosenProject.numOfEmpNeeded;
    int numOfExperienced = chosenProject.minExpEmpNum;
    int numOfDomainNeeded = 1; // special Case
    int numOfSelectedEmployees = 0;

    int domainId = chosenProject.domainExpertId,
            experienceYear = chosenProject.minExperience;

    int ba = numOfEmpNeeded * 0.3,
            dev = numOfEmpNeeded - (2 * ba),
            tester = ba;

    if (isTesting) printf("\nAllotment Work: ", ba, dev, tester);

    struct Employee selectedEmployees[numOfEmpNeeded];
    int indexEmp = 0;

    bool haveExperienced = false, haveDomainPerson = false, haveRequiredEmployees = false;
    bool haveTechLead = false, haveProductOwner = false;

    // Checking for free employees
    int tempNumOfEmpFree = 0;
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {

        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_WORKER &&
            ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS) {
            tempNumOfEmpFree++;
        }
    }
    if (tempNumOfEmpFree >= numOfEmpNeeded) haveRequiredEmployees = true;

    if (!haveRequiredEmployees) {
        printf("\nAllocation cancelled,");
        printf("\nWe don't have required number of employees for this project");
        return;
    }

    // Allotting domainExpert and experienced Employees first
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {

        // DOMAIN EXPERT
        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_WORKER &&
            ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS) {

            if (!haveDomainPerson && ALL_EMP_ARRAY[i].domainExpert == domainId) {
                selectedEmployees[indexEmp] = ALL_EMP_ARRAY[i];
                numOfDomainNeeded--;
                numOfEmpNeeded--;
                ALL_EMP_ARRAY[i].engagedProjects++;
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
                } else if (dev > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_DEVELOPER;
                    dev--;
                } else if (tester > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_TESTER;
                    tester--;
                }

                indexEmp++;

                // EXPERIENCED HERE
            } else if (numOfExperienced > 0 && experienceYear <= ALL_EMP_ARRAY[i].prevExperience) {
                selectedEmployees[indexEmp] = ALL_EMP_ARRAY[i];
                numOfExperienced--;
                numOfEmpNeeded--;
                ALL_EMP_ARRAY[i].engagedProjects++;
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
                } else if (dev > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_DEVELOPER;
                    dev--;
                } else if (tester > 0) {
                    selectedEmployees[indexEmp].roleInProject = MEMBER_TESTER;
                    tester--;
                }
                indexEmp++;
            }

            if (haveExperienced && numOfExperienced == 0) break;
        }
    }

    if (!haveExperienced) {
        printf("\nAllocation cancelled,");
        printf("\nWe don't have experienced people for this project");
        return;
    }

    if (!haveDomainPerson) {
        printf("\nWe don't have domain expert for this project, Please choose another project");
        return;
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

            selectedEmployees[indexEmp] = ALL_EMP_ARRAY[i];
            numOfEmpNeeded--;
            ALL_EMP_ARRAY[i].engagedProjects++;
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
            } else if (dev > 0) {
                selectedEmployees[indexEmp].roleInProject = MEMBER_DEVELOPER;
                dev--;
            } else if (tester > 0) {
                selectedEmployees[indexEmp].roleInProject = MEMBER_TESTER;
                tester--;
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

    // Show Message on console
    printf("\nSuccessful: We have allotted the required Employees to the project.");

    // print the projects selected

    printf("\nAllocation Details: \n");

    printColumnsProject();
    printSingleLineProject(chosenProject);

    printf("\nAllotted Employees Details\n");
    // print selected employees
    printColumnsEmployee();
    for (int i = 0; i < numOfEmpNeeded; ++i) {
        struct Employee emp1 = selectedEmployees[i];
        printSingleLineEmployee(emp1);
    }

}

void allotEmployeeToProject() {

    int chosenId;
    int total = displayProjects(2);

    if (total == 0) printf("\n There are no idle projects left.");
    else printf("\nPlease choose one project to allocate employees to it: ");

    again:
    scanf("%d", &chosenId);
    if (chosenId >= total) {
        printf("\nPlease choose valid project: ");
        goto again;
    }

    if (ALL_PROJECT_ARRAY[chosenId - 1].status != PROJECT_STATUS_IDLE) {
        printf("\nThis project is already inProgress or completed.");
    }

    startProcess(ALL_PROJECT_ARRAY[chosenId - 1]);
}