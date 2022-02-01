#ifndef UNTITLED_ADBHELPER_H
#define UNTITLED_ADBHELPER_H

#include <stdbool.h>

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
    char companyName[100];
    char contactMob[11];
    char contactEmail[100];
    int projectId;
};

extern const int PROJECT_STATUS_IDLE;
extern const int PROJECT_STATUS_COMPLETED;
extern const int PROJECT_STATUS_PROGRESS;

extern const int EMP_STATUS_IDLE;
extern const int EMP_STATUS_HAVE_PROJECT;
extern const int EMP_STATUS_BUSY;

extern const int EMP_DESIG_MANAGER;
extern const int EMP_DESIG_ADMIN;
extern const int EMP_DESIG_WORKER;

extern const int EMP_MAX_PROJECTS;
//extern const int ERROR;

extern const int MEMBER_PRODUCT_OWNER;
extern const int MEMBER_TECH_LEAD;
extern const int MEMBER_BA;
extern const int MEMBER_DEVELOPER;
extern const int MEMBER_TESTER;

extern const char ADDRESS_PROJECT[];
extern const char ADDRESS_EMPLOYEE[];
extern const char ADDRESS_MEMBER[];
extern const char ADDRESS_CLIENT[];
extern const char ADDRESS_LOGIN[];

extern const char FORMAT_PROJECT[];
extern const char FORMAT_EMPLOYEE[];
extern const char FORMAT_MEMBER[];
extern const char FORMAT_CLIENT[];
extern const char FORMAT_LOGIN[];

extern const char FORMAT_PRINT_PROJECT[];
extern const char FORMAT_PRINT_EMPLOYEE[];
extern const char FORMAT_PRINT_MEMBER[];
extern const char FORMAT_PRINT_CLIENT[];
extern const char FORMAT_PRINT_LOGIN[];

extern const char INVALID_INPUT[];

extern const char DOMAIN_ARRAY[][50];
extern const int SIZE_DOMAIN;

extern const char DESIG_ARRAY_EMP[][20];
extern const int SIZE_DESIG;

extern const char COLUMNS_PROJECT[][50];

extern const char COLUMNS_EMPLOYEE[][50];

extern const char COLUMNS_MEMBER[][50];
extern const char COLUMNS_CLIENT[][50];

extern const char COLUMNS_LOGIN[][50];

extern const int SIZE_COLUMNS_EMPLOYEE;
extern const int SIZE_COLUMNS_MEMBER;
extern const int SIZE_COLUMNS_CLIENT;
extern const int SIZE_COLUMNS_LOGIN;
extern const int SIZE_COLUMNS_PROJECT;

extern const bool isTesting;

extern struct Employee ALL_EMP_ARRAY[];
extern int ALL_EMP_ARRAY_SIZE;

extern struct Project ALL_PROJECT_ARRAY[];
extern int ALL_PROJECT_ARRAY_SIZE;

extern struct Member ALL_MEMBER_ARRAY[];
extern int ALL_MEMBER_ARRAY_SIZE;

extern struct Login ALL_LOGIN_ARRAY[];
extern int ALL_LOGIN_ARRAY_SIZE;

extern struct Client ALL_CLIENT_ARRAY[];
extern int ALL_CLIENT_ARRAY_SIZE;

// LoggedInUser
extern struct Login currentUser;

// SINGLE LINE PRINTING

void printSingleLineProject(struct Project project, int number);

void printSingleLineEmployee(struct Employee employee, int number);

void printSingleLineMember(struct Member member, int number);

void printSingleLineLogin(struct Login login, int number);

void printSingleLineClient(struct Client client, int number);

// -------> COLUMNS PRINTING

void printColumnsProject();

void printColumnsEmployee();

void printColumnsClient();

void printColumnsLogin();

void printColumnsMember();

// INITIALIZATION

void updateProjectFile();

void updateEmployeeFile();

void updateMemberFile();

void updateLoginFile();

void updateClientFile();

void initialLoading();

// get id for table

int getIdOfProjectTable();

int getIdOfEmployeeTable();

int getIdOfClientTable();

// -------> REPORTS WORK

void displayEmployeesByWorkStatus(int STATUS, struct Employee array[]);

void displayProjectsByProgressStatus(int STATUS,  struct Project array[]);

void displayAllProjects( struct Project array[]);

void displayAllEmployees();

void displayMembers();

void displayEmployeesForProject(int projectId);

void displayClientByProjectId(int projectId);

int showAllManagersCustom();

void displayEmployeesByDesignation(int designation,  struct Employee array[]);

void displayAllClients();

// ------------> COUNT FUNCTIONS

int getCountProjectByStatus(int status);

int getCountEmployeeByStatus(int empStatus);

int getCountProjectsByBilling(int billed);

int getCountAllProjects();

int getCountAllEmployees();

// -------> GET STRUCTURES BY ID'S

struct Employee getEmployeeById(int empId);

struct Project getProjectById(int projectId);

// -------------> Print ALL Data for testing

void startTestingForFiles();

// --------> INPUT EASE

int takeInputInteger(int startRange, int endRange);

void printList(char a[30][100], int size);

// -------> Validation functions

void takeInputString(char *string, int minLength, int maxLength);

int takeYesOrNo();

void changeProjectStatusToIdle(int projectId);

void resetDatabase();

#endif //UNTITLED_ADBHELPER_H
