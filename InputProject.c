#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

int validate(char *buf) {
    int i;
    for (i = 0; i < strlen(buf); ++i)
        if (!isalpha(buf[i]) && buf[i] != ' ')   // missing index
            return 0;
    return 1;
}

bool isEmailValidB(char mailId[]) {
    int i, p1, p2;
    p1 = p2 = 0;
    for (i = 0; mailId[i] != '\0'; i++) {
        if (mailId[i] == '@')
            p1 = i;
        else if (mailId[i] == '.')
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

// <------------------------------------->

void addClient(int projectId);

void addProjectToCompany();
