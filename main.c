#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Akshay and Vijay Coding here */

const int PROJECT_STATUS_IDLE = 1;
const int PROJECT_STATUS_COMPLETED = 2;
const int PROJECT_STATUS_PROGRESS = 3;

const int EMP_DESIG_MANAGER = 1;
const int EMP_DESIG_ADMIN = 2;
const int EMP_DESIG_WORKER = 3;

const int EMP_MAX_PROJECTS = 5;

const int LOGIN_ROLE_ADMIN = 1;
const int LOGIN_ROLE_MANAGER = 2;

const int MEMBER_PRODUCT_OWNER = 1;
const int MEMBER_TECH_LEAD = 2;
const int MEMBER_BA = 3;
const int MEMBER_DEVELOPER = 4;
const int MEMBER_TESTER = 5;

const char ADDRESS_PROJECT[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\project.txt";
const char ADDRESS_EMPLOYEE[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\employee.txt";
const char ADDRESS_MEMBER[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\member.txt";
const char ADDRESS_CLIENT[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\client.txt";
const char ADDRESS_LOGIN[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\login.txt";

const char FORMAT_PROJECT[100] = "%d|%s|%d|%s|%s|%s|%d|%d|%d|%d|%d|%d|%d\n";
const char FORMAT_EMPLOYEE[100] = "%d|%s|%s|%d|%s|%s|%d|%d|%s|%d|%d\n";
const char FORMAT_MEMBER[100] = "%d|%d|%d\n";
const char FORMAT_CLIENT[100] = "%d|%s|%d|%s|%s|%s\n";
const char FORMAT_LOGIN[100] = "%s|%s|%d|%d";

const char DOMAIN_ARRAY[5][100] = {"Finance", "Banking", "Data Science", "HealthCare", "Education"};

const char COLUMNS_PROJECT[13][50] = {"Id", "Name", "Status", "DeadLine", "Description",
                                      "CreatedOn", "NumEmpNeeded", "ManagerId", "MinExperience",
                                      "MinExpEmpNum", "IsBilled", "DomainExpReq", "ClientId"};

const char COLUMNS_EMPLOYEE[11][50] = {"Id", "Name", "JoiningDate", "Designation", "Email",
                                       "Mobile", "ManagerId", "EngagedProject", "DateOfBirth",
                                       "PrevExperience", "DomainExpert"};

const char COLUMNS_MEMBER[3][50] = {"ProjectId", "EmpId", "EmpRole"};
const char COLUMNS_CLIENT[6][50] = {"ClientId", "personName", "ProjectId", "Company",
                                    "Mobile", "Email"};

const char COLUMNS_LOGIN[4][50] = {"UserName", "Password", "RoleInCompany", "EmployeeId"};

struct Project {
    int id;
    char name[100];
    int status;
    char deadLine[9];
    char description[200];
    char createdOn[9];
    int numOfEmpNeeded;
    int managerId;
    int minExperience;
    int minExpEmpNum;
    int isBilled;
    int domainExpertId;
    int clientId;
};

struct Employee {
    int id;
    char name[100];
    char joiningDate[9];
    int designation;
    char email[100];
    char mobile[11];
    int managerId;
    int engagedProjects;
    char dob[9];
    int prevExperience;
    int domainExpert;
    int roleInProject; // extra, not in text file
};

struct Member {
    int projectId;
    int empId;
    int empRole;
};

struct Login {
    char userName[100];
    char password[30];
    int role;
    int empId;
};

struct Client {
    int clientId;
    char personName[100];
    int projectId;
    char companyName[100];
    char contactMob[11];
    char contactEmail[100];
};

struct Employee ALL_EMP_ARRAY[100];
static int ALL_EMP_ARRAY_SIZE = 0;

struct Project ALL_PROJECT_ARRAY[100];
static int ALL_PROJECT_ARRAY_SIZE = 0;

struct Member ALL_MEMBER_ARRAY[100 * 5];
static int ALL_MEMBER_ARRAY_SIZE = 0;

struct Login ALL_LOGIN_ARRAY[100];
static int ALL_LOGIN_ARRAY_SIZE = 0;

struct Client ALL_CLIENT_ARRAY[100];
static int ALL_CLIENT_ARRAY_SIZE = 0;

// EXTRA for specific case
struct Employee ADD_EMP_ARRAY[100];
static int ADD_EMP_ARRAY_SIZE = 0;

struct Member ADD_MEMBER_ARRAY[100];
static int ADD_MEMBER_ARRAY_SIZE = 0;

// --------------------------------------------------------------

void updateLoginFile() {
    FILE *loginFile = fopen(ADDRESS_LOGIN, "w");

    for (int i = 0; i < ALL_LOGIN_ARRAY_SIZE; ++i) {

        fprintf(loginFile, FORMAT_LOGIN,
                ALL_LOGIN_ARRAY[i].userName, ALL_LOGIN_ARRAY[i].password,
                ALL_LOGIN_ARRAY[i].role, ALL_LOGIN_ARRAY[i].empId);
    }

    fclose(loginFile);
}

void updateProjectFile() {

    FILE *projectFile = fopen(ADDRESS_PROJECT, "w");

    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {

        fprintf(projectFile, FORMAT_PROJECT,
                ALL_PROJECT_ARRAY[i].id, ALL_PROJECT_ARRAY[i].name, ALL_PROJECT_ARRAY[i].status,
                ALL_PROJECT_ARRAY[i].deadLine, ALL_PROJECT_ARRAY[i].description,
                ALL_PROJECT_ARRAY[i].createdOn, ALL_PROJECT_ARRAY[i].numOfEmpNeeded,
                ALL_PROJECT_ARRAY[i].managerId, ALL_PROJECT_ARRAY[i].minExperience,
                ALL_PROJECT_ARRAY[i].minExpEmpNum, ALL_PROJECT_ARRAY[i].isBilled,
                ALL_PROJECT_ARRAY[i].domainExpertId, ALL_PROJECT_ARRAY[i].clientId);
    }

    fclose(projectFile);
}

void updateEmployeeFile() {

    FILE *employeeFile = fopen(ADDRESS_EMPLOYEE, "w");

    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {
        fprintf(employeeFile, FORMAT_EMPLOYEE,
                ALL_EMP_ARRAY[i].id, ALL_EMP_ARRAY[i].name, ALL_EMP_ARRAY[i].joiningDate, ALL_EMP_ARRAY[i].designation,
                ALL_EMP_ARRAY[i].email,
                ALL_EMP_ARRAY[i].mobile, ALL_EMP_ARRAY[i].managerId, ALL_EMP_ARRAY[i].engagedProjects,
                ALL_EMP_ARRAY[i].dob, ALL_EMP_ARRAY[i].prevExperience, ALL_EMP_ARRAY[i].domainExpert);
    }

    fclose(employeeFile);
}

void updateMemberFile() {

    FILE *memberFile = fopen(ADDRESS_MEMBER, "w");

    for (int i = 0; i < ALL_MEMBER_ARRAY_SIZE; ++i) {
        fprintf(memberFile, FORMAT_MEMBER,
                ALL_MEMBER_ARRAY[i].projectId, ALL_MEMBER_ARRAY[i].empId, ALL_MEMBER_ARRAY[i].empRole);
    }

    fclose(memberFile);
}

void convertRowToStructureProject(char row[], struct Project *project) {

    char *p = strtok(row, "|");
    char *array[13];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    /*for (int i = 0; i < 13; ++i){
        printf(array[i]);
        printf(" ");
    }*/

    project->id = atoi(array[0]);
    strcpy(project->name, array[1]);
    project->status = atoi(array[2]);
    strncpy(project->deadLine, array[3], 9);
    strcpy(project->description, array[4]);
    strncpy(project->createdOn, array[5], 9);
    project->numOfEmpNeeded = atoi(array[6]);
    project->managerId = atoi(array[7]);
    project->minExperience = atoi(array[8]);
    project->minExpEmpNum = atoi(array[9]);
    project->isBilled = atoi(array[10]);
    project->domainExpertId = atoi(array[11]);
    project->clientId = atoi(array[12]);
}

void convertRowToEmployee(char row[], struct Employee *employee) {

    char *p = strtok(row, "|");
    char *array[12];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    employee->id = atoi(array[0]);
    strcpy(employee->name, array[1]);
    strncpy(employee->joiningDate, array[2], 9);
    employee->designation = atoi(array[3]);
    strcpy(employee->email, array[4]);
    strcpy(employee->mobile, array[5]);
    employee->managerId = atoi(array[6]);
    employee->engagedProjects = atoi(array[7]);
    strncpy(employee->dob, array[8], 9);
    employee->prevExperience = atoi(array[9]);
    employee->domainExpert = atoi(array[10]);
    employee->roleInProject = atoi(array[11]); // this is useful to add to member table
}

void convertRowToMember(char row[], struct Member *member) {

    char *p = strtok(row, "|");
    char *array[3];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    member->projectId = atoi(array[0]);
    member->empId = atoi(array[1]);
    member->empRole = atoi(array[2]);
}

void convertRowToStructureLogin(char row[], struct Login *login) {
    char *p = strtok(row, "|");
    char *array[4];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    /*for (int i = 0; i < 4; ++i){
        printf(array[i]);
        printf(" ");
    }*/

    strcpy(login->userName, array[0]);
    strcpy(login->password, array[1]);
    login->role = atoi(array[2]);
    login->empId = atoi(array[3]);
}

void getDataOfProjectTable() {

    FILE *fileProject = fopen(ADDRESS_PROJECT, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, fileProject) != NULL) {
        struct Project pr;
        convertRowToStructureProject(tempRow, &pr);
        ALL_PROJECT_ARRAY[index++] = pr;
    }


    ALL_PROJECT_ARRAY_SIZE = index;

    // number of rows is in index
    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        struct Project p1 = ALL_PROJECT_ARRAY[i];
        printf(FORMAT_PROJECT,
               p1.id, p1.name, p1.status, p1.deadLine, p1.description,
               p1.createdOn, p1.numOfEmpNeeded, p1.managerId,
               p1.minExperience, p1.minExpEmpNum, p1.isBilled,
               p1.domainExpertId, p1.clientId);
    }

    fclose(fileProject);
}

void getDataOfEmployeeTable() {

    FILE *empFile = fopen(ADDRESS_EMPLOYEE, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, empFile) != NULL) {
        struct Employee tempEmp;
        convertRowToEmployee(tempRow, &tempEmp);
        ALL_EMP_ARRAY[index++] = tempEmp;
    }

    ALL_EMP_ARRAY_SIZE = index;

    // number of rows is in index
    for (int i = 0; i < index; ++i) {
        struct Employee emp1 = ALL_EMP_ARRAY[i];
        printf(FORMAT_EMPLOYEE,
               emp1.id, emp1.name, emp1.joiningDate, emp1.designation, emp1.email,
               emp1.mobile, emp1.managerId, emp1.engagedProjects,
               emp1.dob, emp1.prevExperience, emp1.domainExpert);
    }

    fclose(empFile);
}

void getDataOfMemberTable() {

    FILE *memberFile = fopen(ADDRESS_MEMBER, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, memberFile) != NULL) {
        struct Member tempMember;
        convertRowToMember(tempRow, &tempMember);
        ALL_MEMBER_ARRAY[index++] = tempMember;
    }

    ALL_MEMBER_ARRAY_SIZE = index;

    // number of rows is in index
    for (int i = 0; i < index; ++i) {
        struct Member member = ALL_MEMBER_ARRAY[i];
        printf(FORMAT_MEMBER,
               member.projectId, member.empId, member.empRole);
    }

    fclose(memberFile);
}

void getDataOfLoginTable() {

    FILE *loginFile = fopen(ADDRESS_LOGIN, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, loginFile) != NULL) {
        struct Login login;
        convertRowToMember(tempRow, &login);
        ALL_LOGIN_ARRAY[index++] = login;
    }

    ALL_LOGIN_ARRAY_SIZE = index;

    // number of rows is in index
    for (int i = 0; i < index; ++i) {
        struct Login login = ALL_LOGIN_ARRAY[i];
        printf(FORMAT_LOGIN,
               login.userName, login.password, login.role, login.empId);
    }

    fclose(loginFile);
}

void initializeApp() {
    // This calls the important startUp functions
    getDataOfProjectTable();
    getDataOfEmployeeTable();
    getDataOfMemberTable();

}

void allotEmployeeToProject(struct Project chosenProject) {

    int numOfEmpNeeded = chosenProject.numOfEmpNeeded;
    int numOfExperienced = chosenProject.minExpEmpNum;
    int numOfDomainNeeded = 1; // special Case
    int numOfSelectedEmployees = 0;

    int domainId = chosenProject.domainExpertId,
            experienceYear = chosenProject.minExperience;

    int ba = numOfEmpNeeded / 0.3,
            dev = ba,
            tester = numOfEmpNeeded - (2 * ba);

    struct Employee arrayEmpSelected[numOfEmpNeeded];
    int indexEmp = 0;

    bool haveExperienced = false, haveDomainPerson = false, haveRequiredEmployees = false;

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
        printf("We don't have required number of employees for this project, "
               "Please Choose another Project");
        return;
    }

    // Checking for domainExpert and experienced Employees
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {

        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_WORKER &&
            ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS) {

            if (!haveDomainPerson && ALL_EMP_ARRAY[i].domainExpert == domainId) {
                arrayEmpSelected[indexEmp++] = ALL_EMP_ARRAY[i];
                numOfDomainNeeded--;
                numOfEmpNeeded--;
                ALL_EMP_ARRAY[i].engagedProjects++;
                haveDomainPerson = true;
                numOfSelectedEmployees++;

                if (ba != 0) {
                    arrayEmpSelected[indexEmp].roleInProject = MEMBER_BA;
                    ba--;
                } else if (dev != 0) {
                    arrayEmpSelected[indexEmp].roleInProject = MEMBER_DEVELOPER;
                    dev--;
                } else if (tester != 0) {
                    arrayEmpSelected[indexEmp].roleInProject = MEMBER_TESTER;
                    tester--;
                }

            } else if (numOfExperienced != 0 && experienceYear <= ALL_EMP_ARRAY[i].prevExperience) {
                arrayEmpSelected[indexEmp++] = ALL_EMP_ARRAY[i];
                numOfExperienced--;
                numOfEmpNeeded--;
                ALL_EMP_ARRAY[i].engagedProjects++;
                numOfSelectedEmployees++;
                if (numOfExperienced == 0) haveExperienced = true;

                if (ba != 0) {
                    arrayEmpSelected[indexEmp].roleInProject = MEMBER_BA;
                    ba--;
                } else if (dev != 0) {
                    arrayEmpSelected[indexEmp].roleInProject = MEMBER_DEVELOPER;
                    dev--;
                } else if (tester != 0) {
                    arrayEmpSelected[indexEmp].roleInProject = MEMBER_TESTER;
                    tester--;
                }

            }
        }
    }

    if (!haveExperienced) {
        printf("We don't have experienced people for this project, Please choose another project");
        return;
    }

    if (!haveDomainPerson) {
        printf("We don't have domain expert for this project, Please choose another project");
        return;
    }

    // Selecting remaining workers
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {

        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_WORKER &&
            ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS &&
            numOfEmpNeeded != 0) {

            bool alreadyChosen = false;

            for (int j = 0; j < numOfSelectedEmployees; ++j) {
                if (arrayEmpSelected->id == ALL_EMP_ARRAY[j].id) {
                    alreadyChosen = true;
                    break;
                }
            }

            if (alreadyChosen) continue;

            if (ba != 0) {
                arrayEmpSelected[indexEmp].roleInProject = MEMBER_BA;
                ba--;
            } else if (dev != 0) {
                arrayEmpSelected[indexEmp].roleInProject = MEMBER_DEVELOPER;
                dev--;
            } else if (tester != 0) {
                arrayEmpSelected[indexEmp].roleInProject = MEMBER_TESTER;
                tester--;
            }

            arrayEmpSelected[indexEmp++] = ALL_EMP_ARRAY[i];
            numOfEmpNeeded--;
            ALL_EMP_ARRAY[i].engagedProjects++;
            numOfSelectedEmployees++;
        }
    }

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
        m.empId = arrayEmpSelected[i].id;
        m.empRole = arrayEmpSelected[i].roleInProject;

        ALL_MEMBER_ARRAY[ALL_MEMBER_ARRAY_SIZE++] = m;
    }

    // Now update all data in the file
    updateEmployeeFile();
    updateProjectFile();
    updateMemberFile();

    // Show Message on console
    printf("We have allotted the required Employees to the project");

    // print the projects selected

    printf("Project Details: \n");
    printf(FORMAT_PROJECT,
           chosenProject.id, chosenProject.name, chosenProject.status, chosenProject.deadLine,
           chosenProject.description,
           chosenProject.createdOn, chosenProject.numOfEmpNeeded, chosenProject.managerId,
           chosenProject.minExperience, chosenProject.minExpEmpNum, chosenProject.isBilled,
           chosenProject.domainExpertId, chosenProject.clientId);


    // print selected employees

    printf("Allotted Employees Details\n");
    for (int i = 0; i < numOfEmpNeeded; ++i) {
        struct Employee emp1 = arrayEmpSelected[i];
        printf(FORMAT_EMPLOYEE,
               emp1.id, emp1.name, emp1.joiningDate, emp1.designation, emp1.email,
               emp1.mobile, emp1.managerId, emp1.engagedProjects,
               emp1.dob, emp1.prevExperience, emp1.domainExpert);
        printf("Role is %d\n", emp1.roleInProject);
    }

}

int main() {

    initializeApp();

    int chosen;
    scanf("%d", &chosen);

    allotEmployeeToProject(ALL_PROJECT_ARRAY[chosen - 1]);
    /*int chosenProject;
    scanf("%d", &chosenProject);

    printf("Allot Employee Called");
    allotEmployeeToProject(ALL_PROJECT_ARRAY[chosenProject - 1]);

    printf("Program Ended");*/
}

char *dateFormat(const char date[9]) {

    char formattedDate[11]; // 17-10-2009
    formattedDate[0] = date[6];
    formattedDate[1] = date[7];
    formattedDate[2] = '-';
    formattedDate[3] = date[4];
    formattedDate[4] = date[5];
    formattedDate[5] = '-';
    formattedDate[6] = date[0];
    formattedDate[7] = date[1];
    formattedDate[8] = date[2];
    formattedDate[9] = date[3];

    char *temp = (char *) &formattedDate;
    return temp;

}