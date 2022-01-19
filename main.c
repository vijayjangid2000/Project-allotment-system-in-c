#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include<conio.h>
#include<ctype.h>

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
const char FORMAT_LOGIN[100] = "%s|%s|%d|%d\n";

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
        convertRowToLogin(tempRow, &login);
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

    // number of rows is in index
    for (int i = 0; i < index; ++i) {
        struct Client client = ALL_CLIENT_ARRAY[i];
        printf(FORMAT_CLIENT,
               client.clientId, client.personName, client.projectId,
               client.companyName, client.contactMob, client.contactEmail);
    }

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

void allotEmployeeToProject(struct Project chosenProject) {

    int numOfEmpNeeded = chosenProject.numOfEmpNeeded;
    int numOfExperienced = chosenProject.minExpEmpNum;
    int numOfDomainNeeded = 1; // special Case
    int numOfSelectedEmployees = 0;

    int domainId = chosenProject.domainExpertId,
            experienceYear = chosenProject.minExperience;

    int ba = numOfEmpNeeded * 0.3,
            dev = numOfEmpNeeded - (2 * ba),
            tester = ba;

    printf("\nAllotment Work: ", ba, dev, tester);

    struct Employee selectedEmployees[numOfEmpNeeded];
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
        printf("\nWe don't have required number of employees for this project, "
               "Please Choose another Project");
        return;
    }

    // Allotting domainExpert and experienced Employees first
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {

        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_WORKER &&
            ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS) {

            if (!haveDomainPerson && ALL_EMP_ARRAY[i].domainExpert == domainId) {
                selectedEmployees[indexEmp] = ALL_EMP_ARRAY[i];
                numOfDomainNeeded--;
                numOfEmpNeeded--;
                ALL_EMP_ARRAY[i].engagedProjects++;
                haveDomainPerson = true;
                numOfSelectedEmployees++;

                if (ba > 0) {
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

            } else if (numOfExperienced > 0 && experienceYear <= ALL_EMP_ARRAY[i].prevExperience) {
                selectedEmployees[indexEmp] = ALL_EMP_ARRAY[i];
                numOfExperienced--;
                numOfEmpNeeded--;
                ALL_EMP_ARRAY[i].engagedProjects++;
                numOfSelectedEmployees++;
                if (numOfExperienced == 0) haveExperienced = true;

                if (ba > 0) {
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
        printf("\nWe don't have experienced people for this project, Please choose another project");
        return;
    }

    if (!haveDomainPerson) {
        printf("\nWe don't have domain expert for this project, Please choose another project");
        return;
    }

    // Selecting remaining workers
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {

        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_WORKER &&
            ALL_EMP_ARRAY[i].engagedProjects < EMP_MAX_PROJECTS &&
            numOfEmpNeeded > 0) {

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

            if (ba > 0) {
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
    printf("\nWe have allotted the required Employees to the project");

    // print the projects selected

    printf("\nProject Details: \n");
    printf(FORMAT_PROJECT,
           chosenProject.id, chosenProject.name, chosenProject.status, chosenProject.deadLine,
           chosenProject.description,
           chosenProject.createdOn, chosenProject.numOfEmpNeeded, chosenProject.managerId,
           chosenProject.minExperience, chosenProject.minExpEmpNum, chosenProject.isBilled,
           chosenProject.domainExpertId, chosenProject.clientId);


    // print selected employees

    printf("\nAllotted Employees Details\n");
    for (int i = 0; i < numOfEmpNeeded; ++i) {
        struct Employee emp1 = selectedEmployees[i];
        printf(FORMAT_EMPLOYEE,
               emp1.id, emp1.name, emp1.joiningDate, emp1.designation, emp1.email,
               emp1.mobile, emp1.managerId, emp1.engagedProjects,
               emp1.dob, emp1.prevExperience, emp1.domainExpert);
        printf("Role is %d\n", emp1.roleInProject);
    }

}

/* Rishabh Task */

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

int mailValidation(char mailid[]) {
    int i, p1, p2;
    p1 = p2 = 0;
    for (i = 0; mailid[i] != '\0'; i++) {
        if (mailid[i] == '@')
            p1 = i;
        else if (mailid[i] == '.')
            p2 = i;
    }
    if (p1 >= 1 && (p2 - p1) >= 1)
        return 1;
    else
        return 0;
}

int generateID() {
    FILE *f;
    int temp = 0;
    char datatoread[1000];
    f = fopen("data1.txt", "r");
    char *token;
    fgets(datatoread, 500, f);
    while (fgets(datatoread, 500, f) != NULL) {
        token = strtok(datatoread, "|");
        temp = atoi(token);
    }
    fclose(f);
    return temp + 1;
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

void addNewEmployee() {

    struct Employee newEmp;

    int operation = 1;

    retake:
    switch (operation) {

        case 1:
            printf("\nEnter Name: ");
            gets(newEmp.name);
            operation++;
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
            printf("\nEnter Designation[1- Manager, 2- Admin, 3- Worker]: ");
            scanf(" %d", &newEmp.designation);
            getchar();
            operation++;
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
            printf("\nEnter Manager Id: ");
            scanf(" %d", &newEmp.managerId);
            getchar();
            operation++;
            break;

        case 6:
            printf("\nEnter Date Of Birth(yyyyMMdd): ");
            gets(newEmp.dob);
            if (atoi(newEmp.dob) <= getSystemDate() && strlen(newEmp.dob) == 8) {
                operation++;
            } else {
                printf("Enter Valid Date");
            }
            break;

        case 7:
            printf("\nEnter Previous Experience (in years): ");
            scanf(" %d", &newEmp.prevExperience);
            getchar();
            operation++;
            break;

        case 8:
            printf("\nChoose Expertise in domain[1- finance, 2 - banking, 3 - dataScience, 4 - healthcare, 5 - education]: ");
            scanf(" %d", &newEmp.domainExpert);
            getchar();
            operation++;
            break;
    }

    if (operation <= 8)goto retake;
    newEmp.id = generateID();
    FILE *f;
    printf("Are You Sure?[y/n]:");
    if (getchar() == 'y') {
        f = fopen("data1.txt", "a");
        fprintf(f, "\n%d|%s|%s|%d|%s|%s|%d|%d|%s|%d|%s", newEmp.id, newEmp.name, newEmp.joiningDate, newEmp.designation,
                newEmp.email, newEmp.mobile, newEmp.managerId, 0, newEmp.dob, newEmp.prevExperience,
                newEmp.domainExpert);
        fclose(f);
    }
}

void addProjectTask() {

}

/* Bhavya Task */

typedef struct project {
    int id;
    char name[100];
    int status;
    char *deadLine;
    char description[200];
    char *createdOn;
    int numOfEmpNeeded;
    int managerId;
    int minExperience;
    int minExpEmpNum;
    int isBilled;
    char *domainExpReq;
    int clientId;
} project;

struct client {
    int clientId;
    char personName[100];
    int id;
    char companyName[30];
    char contactMob[11];
    char contactEmail[30];
};

bool isEmailValid(char mailid[]) {

    int i, p1, p2;
    p1 = p2 = 0;
    for (i = 0; mailid[i] != '\0'; i++) {
        if (mailid[i] == '@')
            p1 = i;
        else if (mailid[i] == '.')
            p2 = i;
    }
    if (p1 > 3 && (p2 - p1) > 3)
        return true;
    else
        return false;

}

int getSystemDateB() {
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

int generateIDB(char filepath[]) {
    FILE *f;
    int temp = 0;
    char dataToRead[1000];
    f = fopen(filepath, "r");
    char *token;
    //fgets(dataToRead,500,f);
    while (fgets(dataToRead, 1000, f) != NULL) {
        token = strtok(dataToRead, "|");
        temp = atoi(token);
    }
    fclose(f);
    return temp + 1;
}

int takeDataOfClient(int id) {
    struct client c;
    char email[100];
    char filepath[100] = "client.txt";
    FILE *f2;
    f2 = fopen(filepath, "a");
    c.clientId = generateID(filepath);
    fflush(stdin);
    printf("\nClient's Name:");
    gets(c.personName);
    c.id = id;
    printf("\nClient's Company:");
    gets(c.companyName);
    printf("\nEnter the contact details of client.");
    printf("\nMobile Number:");
    scanf("%s", &c.contactMob);
    while (1) {
        if (strlen(c.contactMob) == 10 && isNumericString(c.contactMob) == 1) {
            printf("                                                            ");
            break;
        } else {
            printf("\nMobile Number:");
            scanf("%s", &c.contactMob);
        }
    }
    printf("\nEmail:");
    scanf("%s", &email);
    while (1) {
        if (isEmailValid(email)) {
            strcpy(c.contactEmail, email);
            break;
        } else {
            printf("(Invalid Email)");
            printf("\nEmail:");
            scanf("%s", &email);

        }
    }
    fprintf(f2, "\n%d|%s|%d|%s|%s|%s  ", c.clientId, c.personName, c.id, c.companyName, c.contactMob, c.contactEmail);
    fclose(f2);
    return c.clientId;
}

void takeDataFromUser() {
    int deadline, created;
    project *p;
    FILE *f1;
    int n, i, number;
    char filepath[100] = "addproject.txt";
    printf("How many projects you want to enter?");
    scanf("%d", &n);
    p = (project *) calloc(n, sizeof(project));

    for (i = 0; i < n; i++) {
        p[i].id = generateIDB(filepath);
        fflush(stdin);
        printf("\nProject Name:");
        gets(p[i].name);

        p[i].status = 1;

        fflush(stdin);
        printf("\nDescription:");
        gets(p[i].description);

        fflush(stdin);
        created = getSystemDate();
        char s[100];
        sprintf(s, "%d", created);
        p[i].createdOn = s;

        fflush(stdin);
        printf("\nDeadline:");
        scanf("%d", &deadline);

        while (1) {
            if (created < deadline) {
                char s1[10];
                sprintf(s1, "%d", deadline);
                p[i].deadLine = s1;
                break;
            } else {
                printf("(Invalid Date)");
                printf("\nDeadline:");
                scanf("%d", &deadline);
            }
        }
        printf("\nHow many employees will be needed for this project?");
        scanf("%d", &p[i].numOfEmpNeeded);

        fflush(stdin);
        p[i].managerId = -1;

        printf("\nDo you need experienced employee in this project?");
        printf("\nEnter: 1 for Yes\n 2 for No:");
        scanf("%d", &number);
        fflush(stdin);
        if (number == 1) {
            printf("\nwhat should be the minimum experience that an employee must have?");
            scanf("%d", &p[i].minExperience);
            fflush(stdin);
            printf("\nNumber of experienced employees you want.");
            scanf("%d", &p[i].minExpEmpNum);
            if (p[i].numOfEmpNeeded >= p[i].minExpEmpNum) {
                p[i].minExpEmpNum = p[i].minExpEmpNum;
            } else {
                printf("\nNumber of minimum experience employee must be lesser then needed employee");
                printf("\nNumber of experienced employees you want.");
                scanf("%d", &p[i].minExpEmpNum);
            }
        } else {
            p[i].minExperience = -1;
            p[i].minExpEmpNum = -1;
        }

        fflush(stdin);
        printf("\nAny kind of Advanced amount has been given by client?");
        printf("\nEnter: 1 for Yes\n 2 for No\n");
        scanf("%d", &number);
        if (number == 1) {
            p[i].isBilled = 1;
        } else {
            p[i].isBilled = 0;
        }

        fflush(stdin);
        printf("\nDo you need domain expertise in this project?");
        printf("\nEnter: 1 for Yes\n 2 for No");
        fflush(stdin);
        scanf("%d", &number);
        fflush(stdin);
        if (number == 1) {
            printf("\nSelect one:\n1.Finance\n2.Banking\n3.Data Science\n4.Health care\n5.Education\n");
            scanf("%s", &p[i].domainExpReq);

        } else {
            p[i].domainExpReq = "null";
        }

        printf("Enter the details of client associate with this project\n");
        p[i].clientId = takeDataOfClient(p[i].id);

        f1 = fopen(filepath, "a");
        fprintf(f1, "\n%d|%s|%d|%s|%s|%s|%d|%d|%d|%d|%d|%s|%d", p[i].id, p[i].name, p[i].status, p[i].deadLine,
                p[i].description, p[i].createdOn, p[i].numOfEmpNeeded, p[i].managerId, p[i].minExperience,
                p[i].minExpEmpNum, p[i].isBilled, p[i].domainExpReq, p[i].clientId);
        fclose(f1);
    }
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

int main() {
    initializeApp();

    allotEmployeeToProject(ALL_PROJECT_ARRAY[0]);
    addNewEmployee();
}

