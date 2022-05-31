// Project Name: Student Management system
// Date: 26 / 11 / 2021
// Programmers: * B095 AArti Otari
//              * B070 Jay Yadav
//              * B110 Krishna Pandey
//              * B078 Harshvardhan Khimsuriya 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Name
{
    char fName[15];
    char lName[15];
};

struct Address
{
    char hNumber[20];
    char city[15];
    char state[15];
};

struct Student
{
    struct Name name;
    int rollNo;
    struct Address address;
    char email[25];
    long long int ContactNum;
    float SGPA;
    char Course[15];
    char stuId[10];
};

struct Node
{
    struct Student Stu;
    struct Node *next;
} *head = NULL, *last = NULL;

struct info
{

    struct Student *Stu;
    int n;
};

// Prints given linked list
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%s %s %s\n", node->Stu.name.fName, node->Stu.name.lName, node->Stu.stuId);
        node = node->next;
    }
}

// Creates student IDs
void createStuId(char *stuId, char *branch, int rollNo)
{

    char cRollNo[4] = "";
    char aux[4];

    if (rollNo < 10)
    {
        sprintf(aux, "00%d", rollNo);
    }
    else if (rollNo < 100)
    {
        sprintf(aux, "0%d", rollNo);
    }
    else
    {
        sprintf(aux, "%d", rollNo);
    }
    strcat(cRollNo, aux);
    strcpy(stuId, branch);
    strcat(stuId, cRollNo);
}

// Inserts a student in a sorted list
void push(struct Node **head_ref, struct Student student)
{
    struct Node *new_node = (struct Node *)malloc(
        sizeof(struct Node));

    new_node->Stu = student;

    // If first element or deserves to be first
    // strcmp <0 => correct order
    if (*head_ref == NULL || strcmp((*head_ref)->Stu.stuId, student.stuId) > 0)
    {

        new_node->next = (*head_ref);
        (*head_ref) = new_node;
        return;
    }

    struct Node *t = *head_ref;

    while (t->next != NULL && strcmp(t->next->Stu.stuId, student.stuId) < 0)
    {
        t = t->next;
    }
    // strcmp(t->next stuid, newitem stuid) > 0
    new_node->next = t->next;
    t->next = new_node;
}

// Reads student record from a file
struct info readFromFile()
{

    static struct info createInfo;
    struct Student stu[100];
    int i = 0;
    FILE *ptr;

    ptr = fopen("student_record.dat", "r");

    if (ptr == NULL)
    {

        printf("\n=> Error opened file!\n");
        exit(1);
    }

    while (fread(&stu[i], sizeof(struct Student), 1, ptr))
    {

        i++;
    }

    fclose(ptr);

    createInfo.Stu = stu;
    createInfo.n = i;

    return createInfo;
}
// Clears file
void clearFile()
{

    remove("student_record.dat");
}

// Updates student record in the file
void updateToFile()
{
    struct Node *temp = head;
    FILE *ptr = fopen("student_record.dat", "w");

    if (ptr == NULL)
    {

        printf("\nError file opening!\n");
    }

    while (temp != NULL)
    {

        fwrite(&temp->Stu, sizeof(struct Student), 1, ptr);
        temp = temp->next;
    }

    fclose(ptr);
}

//Creates linked list
struct Node *create(struct Node *head, struct Student S[], int n)
{
    struct Node *t, *last;
    head = (struct Node *)malloc(sizeof(struct Node));
    head->Stu = S[0];
    head->next = NULL;
    last = head;

    for (int i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->Stu = S[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
    return head;
}

// insert student nodes
void Insert(struct Node *head, char fname[], char lname[], int rollNo, char hNumber[], char city[], char state[], char email[],
            float SGPA, int contactNum, char course[])
{
    struct Student newStudent;
    strcpy(newStudent.name.fName, fname);
    strcpy(newStudent.name.lName, lname);
    newStudent.rollNo = rollNo;
    strcpy(newStudent.address.hNumber, hNumber);
    strcpy(newStudent.address.city, city);
    strcpy(newStudent.address.state, state);
    strcpy(newStudent.email, email);
    newStudent.SGPA = SGPA;
    newStudent.ContactNum = contactNum;
    strcpy(newStudent.Course, course);
    createStuId(newStudent.stuId, newStudent.Course, newStudent.rollNo);

    push(&head, newStudent);
    updateToFile();
}

// Creates spaces
void space(int i)
{
    while (i > 0)
    {
        printf(" ");
        i--;
    }
}

// Counts total number of students
int stuCount()
{

    struct Node *temp = head;
    int count = 0;

    while (temp != NULL)
    {

        count++;
        temp = temp->next;
    }

    return count;
}

// Deletes selected student record from list
void deleteStudentRecord(char *branch, int rollNo)
{

    struct Node *prevNode = NULL, *currentNode = head;
    int nodes = stuCount(), count = 1;
    char id[10];
    createStuId(id, branch, rollNo);

    while (currentNode != NULL)
    {

        if (count == 1)
        {

            if (strcmp(currentNode->Stu.stuId, id) == 0)
            {

                head = currentNode->next;
                printf("\t\t\t\t=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                free(currentNode);
                updateToFile();
                return;
            }
        }
        else if (count == nodes)
        {

            if (strcmp(currentNode->Stu.stuId, id) == 0)
            {

                printf("\t\t\t\t=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                prevNode->next = NULL;
                free(currentNode);
                updateToFile();
                return;
            }
        }
        else
        {

            if (strcmp(currentNode->Stu.stuId, id) == 0)
            {

                prevNode->next = currentNode->next;
                printf("\t\t\t\t=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                free(currentNode);
                updateToFile();
                return;
            }
        }

        prevNode = currentNode;
        currentNode = currentNode->next;
        count++;
    }

    printf("\t\t\t\t=> Couldn't find Student Record.\n\n");
}

// Displays student record
void DisplayStuDetails(struct Student stu, int count)
{

    printf("\n\t\t\t%d)", count);
    printf(" %s %s ", stu.name.fName, stu.name.lName);
    space(16 - strlen(stu.name.fName) - strlen(stu.name.lName));
    printf("%s", stu.stuId);
    printf("%6d", stu.rollNo);
    printf("%17lld", stu.ContactNum);
    printf("%8s", stu.Course);
    printf("%11.1f", stu.SGPA);
    printf("    %s", stu.email);
    space(23 - strlen(stu.email));
    printf("%s, %s, %s", stu.address.hNumber, stu.address.city, stu.address.state);
}

// Displays given linked list
void DisplayLIST(struct Node *p)
{
    printf("\n\t\t\t");
    for (int i = 0; i < 133; i++)
        printf("=");
    printf("\n\t\t\t%7s%16s%12s%14s%10s%10s%9s%26s\n", "Name", "ID", "Roll No", "Contact No", "Course", "SGPA", "Email",
           "Address");
    printf("\t\t\t");
    for (int i = 0; i < 133; i++)
        printf("=");

    int count = 1;
    while (p)
    {

        DisplayStuDetails(p->Stu, count);
        p = p->next;
        count++;
        printf("\n\n");
    }
}

// Searches student records
void stuSearch(struct Node *head)
{
    int choice = 1;

    
    printf("\t\t\t\t\t\t\t\t1. Search by First name of the student\n");
    printf("\t\t\t\t\t\t\t\t2. Search by  Last name of the student\n");
    printf("\t\t\t\t\t\t\t\t3. Search by   RollNo.  of the student\n");
    printf("\t\t\t\t\t\t\t\t4. Search by   Branch   of the student\n");
    printf("\t\t\t\t\t\t\t\t5. Search by   state    of the student\n");
    printf("\t\t\t\t\t\t\t\t6. Search by   City     of the student\n");
    printf("\t\t\t\t\t\t\t\t7. Search by   SGPA     of the student\n");
    printf("\t\t\t\t\t\t\t\t8. Exit the search menu\n");
    while (choice != 8)
    {
        struct Node *temp = head;
        int flag = 0, count = 0;

        printf("\n\n\t\t\t\tEnter your choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
        {
            char fname[15];
            struct Node *fnameHead = (struct Node *)malloc(sizeof(struct Node));
            fnameHead->next = NULL;

            printf("\t\t\t\tEnter the first name of the student : ");
            scanf("%s", fname);

            while (temp != NULL)
            {

                if (strstr(temp->Stu.name.fName, fname))
                {

                    count++;

                    if (flag == 0)
                    {

                        fnameHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        push(&fnameHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }
            
            if (flag == 1)
            {

                DisplayLIST(fnameHead);
            }

            printf("\t\t\t\t=> %d record/s found!\n", count);
            break;
        }

        case 2:
        {
            char lname[15];
            struct Node *lnameHead = (struct Node *)malloc(sizeof(struct Node));
            lnameHead->next = NULL;

            printf("\t\t\t\tEnter the last name of the student : ");
            scanf("%s", lname);

            while (temp != NULL)
            {
                if (strstr(temp->Stu.name.lName, lname))
                {
                    count++;
                    if (flag == 0)
                    {
                        lnameHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {
                        push(&lnameHead, temp->Stu);
                    }
                }
                temp = temp->next;
            }
            
            if (flag == 1)
            {
                DisplayLIST(lnameHead);
            }

            printf("\t\t\t\t=> %d record/s found!\n", count);
            break;
        }
        case 3:
        {
            int rollNo = 0;
            struct Node *rollNoHead = (struct Node *)malloc(sizeof(struct Node));
            rollNoHead->next = NULL;

            printf("\t\t\t\tEnter the rollNo. of the student : ");
            scanf("%d", &rollNo);

            while (temp != NULL)
            {

                if (temp->Stu.rollNo == rollNo)
                {

                    count++;

                    if (flag == 0)
                    {

                        rollNoHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        push(&rollNoHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }
            
            if (flag == 1)
            {
                DisplayLIST(rollNoHead);
            }

            printf("\t\t\t\t=> %d record/s found!\n", count);
            break;
        }
        case 4:
        {
            char branch[15];
            struct Node *branchHead = (struct Node *)malloc(sizeof(struct Node));
            branchHead->next = NULL;

            printf("\t\t\t\tEnter the branch of the student : ");
            scanf("%s", branch);

            while (temp != NULL)
            {

                if (strstr(temp->Stu.Course, branch) == 0)
                {

                    count++;

                    if (flag == 0)
                    {

                        branchHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        push(&branchHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(branchHead);
            }
            printf("\t\t\t\t=> %d record/s found!\n", count);
            break;
        }
        case 5:
        {
            char state[15];
            struct Node *stateHead = (struct Node *)malloc(sizeof(struct Node));
            stateHead->next = NULL;

            printf("\t\t\t\tEnter the state of the student : ");
            scanf("%s", state);

            while (temp != NULL)
            {

                if (strstr(temp->Stu.address.state, state) == 0)
                {

                    count++;

                    if (flag == 0)
                    {

                        stateHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        push(&stateHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(stateHead);
            }
            printf("\t\t\t\t=> %d record/s found!\n", count);
            break;
        }
        case 6:
        {
            char city[15];
            struct Node *cityHead = (struct Node *)malloc(sizeof(struct Node));
            cityHead->next = NULL;

            printf("\t\t\t\tEnter the city of the student : ");
            scanf("%s", city);

            while (temp != NULL)
            {

                if (strstr(temp->Stu.address.city, city) == 0)
                {

                    count++;

                    if (flag == 0)
                    {

                        cityHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        push(&cityHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(cityHead);
            }
            printf("\t\t\t\t=> %d record/s found!\n", count);
            break;
        }
        case 7:
        {
            float SGPA = 0;
            struct Node *SGPAHead = (struct Node *)malloc(sizeof(struct Node));
            SGPAHead->next = NULL;

            printf("\t\t\t\tEnter the SGPA of the student : ");
            scanf("%f", &SGPA);

            while (temp != NULL)
            {

                if (temp->Stu.SGPA == SGPA)
                {

                    count++;

                    if (flag == 0)
                    {

                        SGPAHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        push(&SGPAHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(SGPAHead);
            }
            printf("\t\t\t\t=> %d record/s found!\n", count);
            break;
        }
        case 8:
            printf("\t\t\t\t=> Successfully exited!\n");
            break;

        default:
            printf("\t\t\t\t=> Invalid input!, please enter a number between 1 to 8\n");
            break;
        }
    }
}

// Tells whether the given Id is present or not
int isPresent(struct Node *head, char *stuId)
{
    struct Node *t = head;
    while (t != NULL)
    {
        if (strcmp(t->Stu.stuId, stuId) == 0)
            return 1;
        t = t->next;
    }
    return 0;
}

// Takes two list and gives the union of the two lists
struct Node *getUnion(struct Node *head1,
                      struct Node *head2)
{
    struct Node *result = NULL;
    struct Node *t1 = head1, *t2 = head2;

    while (t1 != NULL)
    {
        push(&result, t1->Stu);
        t1 = t1->next;
    }

    while (t2 != NULL)
    {
        if (!isPresent(result, t2->Stu.stuId))
            push(&result, t2->Stu);
        t2 = t2->next;
    }

    return result;
}

// Takes two list and gives the intersection of the two lists
struct Node *getIntersection(struct Node *head1,
                             struct Node *head2)
{
    struct Node *result = NULL;
    struct Node *t1 = head1;

    while (t1 != NULL)
    {
        if (isPresent(head2, t1->Stu.stuId))
            push(&result, t1->Stu);
        t1 = t1->next;
    }

    return result;
}

// Takes two list and gives the diff. of the two lists
struct Node *getListDifference(struct Node *head1,
                               struct Node *head2)
{
    struct Node *result = NULL;
    struct Node *t1 = head1;

    while (t1 != NULL)
    {
        if (!isPresent(head2, t1->Stu.stuId))
            push(&result, t1->Stu);
        t1 = t1->next;
    }

    return result;
}

// Takes two list and gives the symmetric diff. of the two lists
struct Node *getSymmetricDifference(struct Node *head1,
                                    struct Node *head2)
{
    struct Node *result = NULL;
    struct Node *t1 = head1;

    while (t1 != NULL)
    {
        if (!isPresent(head2, t1->Stu.stuId))
            push(&result, t1->Stu);
        t1 = t1->next;
    }

    struct Node *t2 = head2;

    while (t2 != NULL)
    {
        if (!isPresent(head1, t2->Stu.stuId))
            push(&result, t2->Stu);
        t2 = t2->next;
    }

    return result;
}

// Gives student record through ID
struct Student getStudentFromId(struct Node *head, char stuId[20])
{
    struct Node *p = head;
    while (p != NULL)
    {
        if (strcmp(p->Stu.stuId, stuId) == 0)
            return p->Stu;
        p = p->next;
    }
    printf("\n\t\t\t\t=> Student record not found\n");
}

// Updates student record
void UpdateUsingStuID(struct Node *head)
{
    char key[10];
    struct Node *p = head;
    int choice = 0;

    printf("\t\t\t\tEnter Student ID: ");
    scanf("%s", key);

    if (isPresent(head, key) == 0)
    {
        printf("\n\t\t\t\t=> This Student ID do not exist.\n");
    }
    else
    {
        while (p)
        {

            if (strcmp(p->Stu.stuId, key) == 0)
            {
                break;
            }

            p = p->next;
        }
        printf("\t\t\t\t\t\t\t\t# Select from menu:\n\t\t\t\t\t\t\t\t1. Update Name\n\t\t\t\t\t\t\t\t2. Update Roll No\n\t\t\t\t\t\t\t\t3. Update Contact No\n\t\t\t\t\t\t\t\t4. Update Email\n\t\t\t\t\t\t\t\t5. Update Course\n\t\t\t\t\t\t\t\t6. Update Address\n\t\t\t\t\t\t\t\t7. Update SGPA\n\t\t\t\t\t\t\t\t8. Exit \n");
        while (choice != 8)
        {
            printf("\t\t\t\tEnter your choice for what you want to update: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
            {
                printf("\n\t\t\t\tEnter the new first name: ");
                scanf("%s", p->Stu.name.fName);
                printf("\t\t\t\tEnter the new last name: ");
                scanf("%s", p->Stu.name.lName);
                printf("\t\t\t\t=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 2:
            {
                printf("\n\t\t\t\t\t\t\t\tEnter the new Roll no: ");
                scanf("%d", &p->Stu.rollNo);
                printf("\t\t\t\t\t\t\t\t=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 3:
            {
                printf("\n\t\t\t\tEnter new Contact Number: ");
                scanf("%lld", &p->Stu.ContactNum);
                printf("\t\t\t\t=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 4:
            {
                printf("\n\t\t\t\tEnter new Email: ");
                scanf("%s", p->Stu.email);
                printf("\t\t\t\t=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 5:
            {
                printf("\n\t\t\t\tEnter new Course: ");
                scanf("%s", p->Stu.Course);
                printf("\t\t\t\t=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 6:
            {
                printf("\n\t\t\t\tEnter the new House number: ");
                scanf("%s", p->Stu.address.hNumber);
                printf("\t\t\t\tEnter the new City: ");
                scanf("%s", p->Stu.address.city);
                printf("\t\t\t\tEnter the new State: ");
                scanf("%s", p->Stu.address.state);
                printf("\t\t\t\t=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 7:
            {
                printf("\n\t\t\t\tEnter the new SGPA: ");
                scanf("%f", &p->Stu.SGPA);
            }
            case 8:
            {
                updateToFile();
                printf("\t\t\t\t=> Successfully exited!\n\n");
                break;
            }
            break;
            default:
                printf("\t\t\t\t=> Invalid input! please enter a number between 1 to 6\n\n");
                break;
            }
        }
    }
}

// modifies existing student record
void modify(struct Node* head, char* key, char* fname, char* lname, int rollNo, char* hNumber, char* city, char* state, char* email, float SGPA, long long int contactNum, char* course) {

struct Node *p = head;

    while (p)
        {

            if (strcmp(p->Stu.stuId, key) == 0)
            {
                break;
            }

            p = p->next;
        }

    strcpy(p->Stu.name.fName, fname);
    strcpy(p->Stu.name.lName, lname);
    p->Stu.rollNo = rollNo;
    strcpy(p->Stu.address.hNumber, hNumber);
    strcpy(p->Stu.address.city, city);
    strcpy(p->Stu.address.state, state);
    strcpy(p->Stu.email, email);
    p->Stu.SGPA = SGPA;
    p->Stu.ContactNum = contactNum;
    strcpy(p->Stu.Course, course);

    updateToFile();
}

// Welcome message
void bigWelcome()
{
    printf("\n\t\t\t\t\t\t       **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t\t\t\t             =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t\t\t             =                  WELCOME                  =");
    printf("\n\t\t\t\t\t\t             =                    TO                     =");
    printf("\n\t\t\t\t\t\t             =               Student Record              =");
    printf("\n\t\t\t\t\t\t             =                 MANAGEMENT                =");
    printf("\n\t\t\t\t\t\t             =                   SYSTEM                  =");
    printf("\n\t\t\t\t\t\t             =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t\t\t       **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
}

// Main function
int main()
{
    head = create(head, readFromFile().Stu, readFromFile().n);

    bigWelcome();
    printf("\n\n\t\t\t\t   =================================== Student Management System ===================================\n");
    printf("\t\t\t\t\t\t\t*****************************************************\n");
    printf("\t\t\t\t\t\t\t\t\t1. Add Student\n");
    printf("\t\t\t\t\t\t\t\t\t2. Modify Student\n");
    printf("\t\t\t\t\t\t\t\t\t3. Show All Students\n");
    printf("\t\t\t\t\t\t\t\t\t4. Show a student's details\n");
    printf("\t\t\t\t\t\t\t\t\t5. Remove Student\n");
    printf("\t\t\t\t\t\t\t\t\t6. Search Student\n");
    printf("\t\t\t\t\t\t\t\t\t7. Exit\n");
    printf("\t\t\t\t\t\t\t*****************************************************\n");
    while (1)
    {
        printf("\n\n\t\t\t\tEnter Option :--> ");
        int option;
        scanf("%d", &option);
        printf("\n");
        switch (option)
        {
        case 1: // insert student or modify existing student
        {   
            printf("\n\t\t\t\t\t\t\t\t# STUDENT INSERTION / MODIFICAION MENU\n\n");

            int count, rollNo, contactNum;
            float SGPA;
            char firstName[20], lastName[20], stuId[20], Course[20], email[20], hNumber[20], city[20], state[20];
            printf("\t\t\t\tEnter first name : ");
            scanf("%s", firstName);
            printf("\t\t\t\tEnter last name : ");
            scanf("%s", lastName);
            printf("\t\t\t\tEnter student roll No : ");
            scanf("%d", &rollNo);
            printf("\t\t\t\tEnter Contact Number : ");
            scanf("%d", &contactNum);
            printf("\t\t\t\tEnter Enrollment Course : ");
            scanf("%s", Course);
            printf("\t\t\t\tEnter SGPA : ");
            scanf("%f", &SGPA);
            printf("\t\t\t\tEnter email id : ");
            scanf("%s", email);
            printf("\t\t\t\tEnter home number : ");
            scanf("%s", hNumber);
            printf("\t\t\t\tEnter city : ");
            scanf("%s", city);
            printf("\t\t\t\tEnter state : ");
            scanf("%s", state);
            createStuId(stuId, Course, rollNo);

            if (isPresent(head, stuId)) {

                modify(head, stuId, firstName, lastName, rollNo, hNumber, city, state, email, SGPA, contactNum, Course);
                printf("\n\t\t\t\t=> Student record of %s got successfully updates!\n", stuId);
            }
            else {
        
                Insert(head, firstName, lastName, rollNo, hNumber, city, state, email, SGPA, contactNum, Course);
                printf("\n\t\t\t\t=> Insertion is succesful.\n\n");
            }
        }
        break;
        case 2: // update student record
            
            printf("\n\t\t\t\t\t\t\t\t# STUDENT UPDATION MENU\n\n");
            
            UpdateUsingStuID(head);
            break;
        case 3: // display student record
        
            printf("\n\t\t\t\t\t\t\t\t# ALL STUDENTS DISPLAY MENU\n\n");

            DisplayLIST(head);
            break;
        case 4: //show student detail.
        {   
            printf("\n\t\t\t\t\t\t\t\t# STUDENT DETAILS MENU\n\n");

            int rollNo;
            char branch[20], stuId[20];
            printf("\t\t\t\tEnter student's branch: ");
            scanf("%s", branch);
            printf("\t\t\t\tEnter student's roll no:");
            scanf("%d", &rollNo);
            createStuId(stuId, branch, rollNo);
            struct Student stu = getStudentFromId(head, stuId);

            if (strcmp(stu.stuId, stuId) == 0)
            {
                DisplayStuDetails(stu, 1);
            }
        }
            break;
        case 5: // delete student

            printf("\n\t\t\t\t\t\t\t\t# STUDENT DELETION MENU\n\n");

            int rollNo;
            char branch[20];
            printf("\t\t\t\tEnter student's branch: ");
            scanf("%s", branch);
            printf("\t\t\t\tEnter student's roll no:");
            scanf("%d", &rollNo);
            deleteStudentRecord(branch, rollNo);
            break;
        case 6: // search student

            printf("\n\t\t\t\t\t\t\t\t# STUDENT SEARCHING MENU\n\n");

            stuSearch(head);
            break;
        case 7: // exit
            printf("\n\t\t\t\t=> THANK YOU FOR VISITING!.\n\n");
            return 0;
        default: // invalid option
            printf("\n\t\t\t\t=> ENTER A VALID OPTION!\n\n");
        }
    }
    return 0;
}
