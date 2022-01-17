#include <stdio.h>

/* Akshay and Vijay Coding here */

struct project {
    int id;
    char name[100];
    int status;
    char deadLine[8];
    char description[2000];
    char createdOn[8];
    int numOfEmpNeeded;
    int managerId;
    int minExperience;
    int minExpEmpNum;
    int isBilled;
    int memberTblId;
    char domainExpReq[5];
    int clientId;
};

struct employee {
    int id;
    char name[20];
    char joiningDate[8];
    int designation;
    char email[20];
    char mobile[10];
    int managerId;
    int engagedProjects;
    char dob[8];
    int prevExperience;
    char domainExpert[5];
};

struct member {
    int projectId;
    int empId;
    int empRole;
};

struct login {
    char userName[30];
    char password[30];
    int role;
    int empId;
};

struct client {
    int clientId;
    char personName[100];
    int projectId;
    char companyName[30];
    char contactMob[10];
    char contactEmail[30];
};

int main() {

}

// function to change the status of project
void function(){
    char path[300] = "C:\\Users\\Lenovo\\Desktop\\MyApp\\project.txt";

}
