#include <stdio.h>
#include <string.h>

void createStuId(char* stuId, char* branch, int rollNo) {
    
    char cRollNo[3] = {'0'};
    char aux[3];

    sprintf(aux, "%d", rollNo);
    strcat(cRollNo, aux);
    strcpy(stuId, branch);
    strcat(stuId, cRollNo);
}

int main() {

    char branch[] = "CSE";
    int rollNo = 78;
    char stuId[6];
    createStuId(stuId, branch, rollNo);

    printf("Student ID : %s", stuId);

    return 0;
}