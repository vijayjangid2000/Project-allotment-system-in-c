//
// Created by Lenovo on 21-01-2022.
//

#ifndef UNTITLED_UTILITY_H
#define UNTITLED_UTILITY_H

#include <stdbool.h>

extern const int PROJECT_STATUS_IDLE;
extern const int PROJECT_STATUS_COMPLETED;
extern const int PROJECT_STATUS_PROGRESS;
extern const int PROJECT_BILLED;
extern const int PROJECT_NOT_BILLED;

extern const int EMP_DESIG_MANAGER;
extern const int EMP_DESIG_ADMIN;
extern const int EMP_DESIG_WORKER;

extern const int EMP_MAX_PROJECTS;
//extern const int ERROR;

extern const int LOGIN_ROLE_ADMIN;
extern const int LOGIN_ROLE_MANAGER;

extern const int MEMBER_PRODUCT_OWNER;
extern const int MEMBER_TECH_LEAD;
extern const int MEMBER_BA;
extern const int MEMBER_DEVELOPER;
extern const int MEMBER_TESTER;

const char ADDRESS_PROJECT[100];
const char ADDRESS_EMPLOYEE[100];
const char ADDRESS_MEMBER[100];
const char ADDRESS_CLIENT[100];
const char ADDRESS_LOGIN[100];

const char FORMAT_PROJECT[100];
const char FORMAT_EMPLOYEE[100];
const char FORMAT_MEMBER[100];
const char FORMAT_CLIENT[100];
const char FORMAT_LOGIN[100];

const char FORMAT_PRINT_PROJECT[100];
const char FORMAT_PRINT_EMPLOYEE[100];
const char FORMAT_PRINT_MEMBER[100];
const char FORMAT_PRINT_CLIENT[100];
const char FORMAT_PRINT_LOGIN[100];

const char DOMAIN_ARRAY[5][100];
extern const int SIZE_DOMAIN;

const char DESIG_ARRAY_EMP[3][100];
extern const int SIZE_DESIG;

const char COLUMNS_PROJECT[13][50];

const char COLUMNS_EMPLOYEE[11][50];

const char COLUMNS_MEMBER[3][50];
const char COLUMNS_CLIENT[6][50];

const char COLUMNS_LOGIN[4][50];

extern const int SIZE_COLUMNS_EMPLOYEE;
extern const int SIZE_COLUMNS_MEMBER;
extern const int SIZE_COLUMNS_CLIENT;
extern const int SIZE_COLUMNS_LOGIN;
extern const int SIZE_COLUMNS_PROJECT;

extern const bool isTesting;

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
extern int ALL_EMP_ARRAY_SIZE;

struct Project ALL_PROJECT_ARRAY[100];
extern int ALL_PROJECT_ARRAY_SIZE;

struct Member ALL_MEMBER_ARRAY[100 * 5];
extern int ALL_MEMBER_ARRAY_SIZE;

struct Login ALL_LOGIN_ARRAY[100];
extern int ALL_LOGIN_ARRAY_SIZE;

struct Client ALL_CLIENT_ARRAY[100];
extern int ALL_CLIENT_ARRAY_SIZE;

// SINGLE LINE PRINTING

void printSingleLineProject(struct Project project);

void printSingleLineEmployee(struct Employee employee);

void printSingleLineMember(struct Member member);

void printSingleLineLogin(struct Login login);

void printSingleLineClient(struct Client client);

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

void convertRowToProject(char row[], struct Project *project);

void convertRowToEmployee(char row[], struct Employee *employee);

void convertRowToMember(char row[], struct Member *member);

void convertRowToLogin(char row[], struct Login *login);

void convertRowToClient(char row[], struct Client *client);

void getDataOfProjectTable();

void getDataOfEmployeeTable();

void getDataOfMemberTable();

void getDataOfLoginTable();

void getDataOfClientTable();

void initializeApp();

// -------> REPORTS WORK

void displayEmployees(int STATUS);

int displayProjects(int STATUS);

void displayMembers();

void displayEmployeesForProject(int projectId);

// -------> GET STRUCTURES BY ID'S

struct Employee getEmployeeById(int empId);

struct Project getProjectById(int projectId);

// -------------> Print ALL Data for testing

void testPrintClients();

void testPrintEmployees();

void testPrintMembers();

void testPrintProjects();

void testPrintLogins();

#endif //UNTITLED_UTILITY_H
