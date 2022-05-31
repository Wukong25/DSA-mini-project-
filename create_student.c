#include "main_v4.c"

// Creates a student
struct Student createStu() {

    struct Student S;
    
    printf("Enter the First Name of the student : ");
    scanf("%[^\n]%*c", S.name.fName);
    printf("Enter the Last Name of the student : ");
    scanf("%[^\n]%*c", S.name.lName);
    printf("Enter the RollNo. of the student : ");
    scanf("%d%*c", &S.rollNo);
    printf("Enter the HouseNo. of the student : ");
    scanf("%[^\n]%*c", S.address.hNumber);
    printf("Enter the City of the student : ");
    scanf("%[^\n]%*c", S.address.city);
    printf("Enter the State of the student : ");
    scanf("%[^\n]%*c", S.address.state);
    printf("Enter the Email of the student : ");
    scanf("%[^\n]%*c", S.email);
    printf("Enter the ContactNo. of the student : ");
    scanf("%d%*c", &S.ContactNum);
    printf("Enter the Course of the student : ");
    scanf("%[^\n]%*c", S.Course);
    printf("Enter the SGPA of the student : ");
    scanf("%d%*c", &S.SGPA);
    createStuId(S.stuId, S.Course, S.rollNo);

    return S;
}