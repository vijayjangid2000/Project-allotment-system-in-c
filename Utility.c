#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<conio.h>

const int PROJECT_STATUS_IDLE = 1;
const int PROJECT_STATUS_COMPLETED = 2;
const int PROJECT_STATUS_PROGRESS = 3;
const int PROJECT_BILLED = 1;
const int PROJECT_NOT_BILLED = 0;

const int EMP_DESIG_MANAGER = 1;
const int EMP_DESIG_ADMIN = 2;
const int EMP_DESIG_WORKER = 3;

const int EMP_MAX_PROJECTS = 5;
const int ERROR = -1;

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

const char FORMAT_PROJECT[100] = "\n%d|%s|%d|%s|%s|%s|%d|%d|%d|%d|%d|%d|%d";
const char FORMAT_EMPLOYEE[100] = "\n%d|%s|%s|%d|%s|%s|%d|%d|%s|%d|%d";
const char FORMAT_MEMBER[100] = "\n%d|%d|%d";
const char FORMAT_CLIENT[100] = "\n%d|%s|%d|%s|%s|%s";
const char FORMAT_LOGIN[100] = "\n%s|%s|%d|%d";

const char FORMAT_PRINT_PROJECT[100] = "\n%d %s %d %s %s %s %d %d %d %d %d %d %d";
const char FORMAT_PRINT_EMPLOYEE[100] = "\n%d %s %s %d %s %s %d %d %s %d %d";
const char FORMAT_PRINT_MEMBER[100] = "\n%d %d %d";
const char FORMAT_PRINT_CLIENT[100] = "\n%d %s %d %s %s %s";
const char FORMAT_PRINT_LOGIN[100] = "\n%s %s %d %d";

const char DOMAIN_ARRAY[5][100] = {"Finance", "Banking", "Data Science",
                                   "HealthCare", "Education"};
const int SIZE_DOMAIN = 5;

const char DESIG_ARRAY_EMP[3][100] = {"Manager", "Admin", "Worker"};
const int SIZE_DESIG = 3;

const char COLUMNS_PROJECT[13][50] = {"Id", "Name", "Status", "DeadLine", "Description",
                                      "CreatedOn", "NumEmpNeeded", "ManagerId", "MinExperience",
                                      "MinExpEmpNum", "IsBilled", "DomainExpReq", "ClientId"};

const char COLUMNS_EMPLOYEE[11][50] = {"Id", "Name", "JoiningDate", "Designation", "Email",
                                       "Mobile", "ManagerId", "EngagedProject", "DateOfBirth",
                                       "PrevExperience", "DomainExpert"};

const char COLUMNS_MEMBER[3][50] = {"ProjectId", "EmpId", "EmpRole"};
const char COLUMNS_CLIENT[6][50] = {"ClientId", "Name", "ProjectId", "Company",
                                    "Mobile", "Email"};

const char COLUMNS_LOGIN[4][50] = {"UserName", "Password", "RoleInCompany", "EmployeeId"};

const int SIZE_COLUMNS_EMPLOYEE = 11;
const int SIZE_COLUMNS_MEMBER = 3;
const int SIZE_COLUMNS_CLIENT = 6;
const int SIZE_COLUMNS_LOGIN = 4;
const int SIZE_COLUMNS_PROJECT = 13;

const bool isTesting = false;

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

// SINGLE LINE PRINTING

void printSingleLineProject(struct Project project) {
    printf(FORMAT_PROJECT,
           project.id, project.name, project.status, project.deadLine, project.description,
           project.createdOn, project.numOfEmpNeeded, project.managerId,
           project.minExperience, project.minExpEmpNum, project.isBilled,
           project.domainExpertId, project.clientId);
}

void printSingleLineEmployee(struct Employee employee) {
    printf(FORMAT_PRINT_EMPLOYEE,
           employee.id, employee.name, employee.joiningDate,
           employee.designation,
           employee.email,
           employee.mobile, employee.managerId, employee.engagedProjects,
           employee.dob, employee.prevExperience, employee.domainExpert);
}

void printSingleLineMember(struct Member member) {

    printf(FORMAT_PRINT_MEMBER,
           member.projectId, member.empId, member.empRole);
}

void printSingleLineLogin(struct Login login) {

    printf(FORMAT_PRINT_LOGIN,
           login.userName, login.password, login.role, login.empId);

}

void printSingleLineClient(struct Client client) {

    printf(FORMAT_PRINT_CLIENT,
           client.clientId, client.personName, client.projectId,
           client.companyName, client.contactMob, client.contactEmail);

}

// -------> COLUMNS PRINTING

void printColumnsProject() {
    printf("\n");
    for (int i = 0; i < SIZE_COLUMNS_PROJECT; ++i) {
        printf(" %s", COLUMNS_PROJECT[i]);
    }
}

void printColumnsEmployee() {
    printf("\n");
    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i) {
        printf(" %s", COLUMNS_EMPLOYEE[i]);
    }
}

void printColumnsClient() {
    printf("\n");
    for (int i = 0; i < SIZE_COLUMNS_CLIENT; ++i) {
        printf(" %s", COLUMNS_CLIENT[i]);
    }
}

void printColumnsLogin() {
    printf("\n");
    for (int i = 0; i < SIZE_COLUMNS_LOGIN; ++i) {
        printf(" %s", COLUMNS_LOGIN[i]);
    }
}

void printColumnsMember() {
    printf("\n");
    for (int i = 0; i < SIZE_COLUMNS_MEMBER; ++i) {
        printf(" %s", COLUMNS_MEMBER[i]);
    }
}

// INITIALIZATION

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

void updateLoginFile() {

    FILE *loginFile = fopen(ADDRESS_LOGIN, "w");
    for (int i = 0; i < ALL_LOGIN_ARRAY_SIZE; ++i) {
        fprintf(loginFile, FORMAT_LOGIN,
                ALL_LOGIN_ARRAY[i].userName, ALL_LOGIN_ARRAY[i].password,
                ALL_LOGIN_ARRAY[i].role, ALL_LOGIN_ARRAY[i].empId);
    }

    fclose(loginFile);
}

void updateClientFile() {

    FILE *clientFile = fopen(ADDRESS_CLIENT, "w");
    for (int i = 0; i < ALL_CLIENT_ARRAY_SIZE; ++i) {
        fprintf(clientFile, FORMAT_CLIENT,
                ALL_CLIENT_ARRAY[i].clientId, ALL_CLIENT_ARRAY[i].personName,
                ALL_CLIENT_ARRAY[i].projectId, ALL_CLIENT_ARRAY[i].companyName,
                ALL_CLIENT_ARRAY[i].contactMob, ALL_CLIENT_ARRAY[i].contactEmail);
    }

    fclose(clientFile);
}

void convertRowToProject(char row[], struct Project *project) {

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

void convertRowToLogin(char row[], struct Login *login) {
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

void convertRowToClient(char row[], struct Client *client) {

    char *p = strtok(row, "|");
    char *array[6];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    client->clientId = atoi(array[0]);
    strcpy(client->personName, array[1]);
    client->projectId = atoi(array[2]);
    strcpy(client->companyName, array[3]);
    strcpy(client->contactMob, array[4]);
    strcpy(client->contactEmail, array[5]);
}

void getDataOfProjectTable() {

    FILE *fileProject = fopen(ADDRESS_PROJECT, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, fileProject) != NULL) {
        struct Project pr;
        convertRowToProject(tempRow, &pr);
        ALL_PROJECT_ARRAY[index++] = pr;
    }

    ALL_PROJECT_ARRAY_SIZE = index;
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

    fclose(memberFile);
}

void getDataOfLoginTable() {

    FILE *loginFile = fopen(ADDRESS_LOGIN, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, loginFile) != NULL) {
        struct Login login;
        convertRowToLogin(tempRow, &login);
        ALL_LOGIN_ARRAY[index++] = login;
    }

    ALL_LOGIN_ARRAY_SIZE = index;

    fclose(loginFile);
}

void getDataOfClientTable() {

    FILE *clientFile = fopen(ADDRESS_CLIENT, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, clientFile) != NULL) {
        struct Client client;
        convertRowToClient(tempRow, &client);
        ALL_CLIENT_ARRAY[index++] = client;
    }

    ALL_CLIENT_ARRAY_SIZE = index;

    fclose(clientFile);
}

void initializeApp() {
    // This calls the important startUp functions
    getDataOfProjectTable();
    getDataOfEmployeeTable();
    getDataOfMemberTable();
    getDataOfClientTable();
    getDataOfLoginTable();
}

// -------> REPORTS WORK

void displayEmployees(int STATUS) {

    printf("Idle Employee Report");

    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i) {
        printf(" %s", COLUMNS_EMPLOYEE[i]);
    }

    printf("\n");

    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {

        if (STATUS == EMP_MAX_PROJECTS
            && ALL_EMP_ARRAY[i].engagedProjects == EMP_MAX_PROJECTS) {
            printSingleLineEmployee(ALL_EMP_ARRAY[i]);
        } else if (ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS) {
            printSingleLineEmployee(ALL_EMP_ARRAY[i]);
        }
    }
}

int displayProjects(int STATUS) {

    printColumnsProject();
    int projectsCount = 0;

    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        struct Project temp = ALL_PROJECT_ARRAY[i];
        if (temp.status == STATUS) {
            printSingleLineProject(temp);
            projectsCount++;
        }
    }
    return projectsCount;
}

void displayMembers() {

    for (int i = 0; i < SIZE_COLUMNS_MEMBER; ++i) {
        printf(" %s", COLUMNS_MEMBER[i]);
    }

    printf("\n");

    for (int i = 0; i < ALL_MEMBER_ARRAY_SIZE; ++i) {
        printSingleLineMember(ALL_MEMBER_ARRAY[i]);
    }
}

void displayEmployeesForProject(int projectId) {

    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i)
        printf(" %s", COLUMNS_EMPLOYEE[i]);

    printf("\n");
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {
        if (ALL_EMP_ARRAY[i].id == projectId)
            printSingleLineEmployee(ALL_EMP_ARRAY[i]);
    }
}

// -------> GET STRUCTURES BY ID'S

struct Employee getEmployeeById(int empId) {
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {
        if (ALL_EMP_ARRAY[i].id == empId)return ALL_EMP_ARRAY[i];
    }
}

struct Project getProjectById(int projectId) {
    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; i++) {
        if (ALL_PROJECT_ARRAY[i].id == projectId)
            return ALL_PROJECT_ARRAY[i];
    }
}

// -------------> Print ALL Data for testing

void testPrintClients() {
    for (int i = 0; i < ALL_CLIENT_ARRAY_SIZE; ++i) {
        struct Client client = ALL_CLIENT_ARRAY[i];
        printSingleLineClient(client);
    }
}

void testPrintEmployees() {
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {
        struct Employee emp1 = ALL_EMP_ARRAY[i];
        printSingleLineEmployee(emp1);
    }
}

void testPrintMembers() {
    for (int i = 0; i < ALL_MEMBER_ARRAY_SIZE; ++i) {
        struct Member member = ALL_MEMBER_ARRAY[i];
        printSingleLineMember(member);
    }
}

void testPrintProjects() {
    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        struct Project p1 = ALL_PROJECT_ARRAY[i];
        printSingleLineProject(p1);
    }
}

void testPrintLogins() {
    for (int i = 0; i < ALL_LOGIN_ARRAY_SIZE; ++i) {
        struct Login login = ALL_LOGIN_ARRAY[i];
        printSingleLineLogin(login);
    }
}