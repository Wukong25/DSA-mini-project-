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

void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%s ", node->Stu.stuId);
        node = node->next;
    }
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

// Writes student record to a file
void writeToFile()
{

    struct Student S = last->Stu;
    FILE *ptr;

    ptr = fopen("student_record.dat", "a");

    if (ptr == NULL)
    {

        printf("\n=> Error opened file!\n");
        exit(1);
    }

    fwrite(&S, sizeof(struct Student), 1, ptr);

    fclose(ptr);
}

// Updates student record in the file
void updateToFile()
{
    struct Node *temp = head;
    FILE *ptr = fopen("student_record.dat", "w");

    if (ptr == NULL)
    {

        printf("\n=> Error file opening!\n");
    }

    while (temp != NULL)
    {

        fwrite(&temp->Stu, sizeof(struct Student), 1, ptr);
        temp = temp->next;
    }

    fclose(ptr);
}

//create LL
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
void Insert(struct Node *ahead, struct Student Stu)
{
    struct Node *t, *p;
    p = ahead;

    if (head == NULL)
    {

        head = (struct Node *)malloc(sizeof(struct Node));
        head->Stu = Stu;
        head->next = NULL;
        last = head;
    }
    else
    {

        while (p->next != NULL)
        {
            p = p->next;
        }
        t = (struct Node *)malloc(sizeof(struct Node));
        t->Stu = Stu;
        t->next = NULL;
        p->next = t;
        last = t;
    }

    printf("\n=> Insertion is succesful.\n\n");
}

void space(int i)
{
    while (i > 0)
    {
        printf(" ");
        i--;
    }
}

// Create Students Unique ID
void createStuId(char *stuId, char *branch, int rollNo)
{

    char cRollNo[4] = "";
    char aux[4];

    if (rollNo < 10)
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
                printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                free(currentNode);
                deleteFromFile();
                return;
            }
        }
        else if (count == nodes)
        {

            if (strcmp(currentNode->Stu.stuId, id) == 0)
            {

                printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                prevNode->next = NULL;
                free(currentNode);
                deleteFromFile();
                return;
            }
        }
        else
        {

            if (strcmp(currentNode->Stu.stuId, id) == 0)
            {

                prevNode->next = currentNode->next;
                printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                free(currentNode);
                deleteFromFile();
                return;
            }
        }

        prevNode = currentNode;
        currentNode = currentNode->next;
        count++;
    }

    printf("=> Student record didn't found!\n\n");
    return;
}

void DisplayStuDetails(struct Student stu, int count)
{

    printf("\n%d)", count);
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

void DisplayLIST(struct Node *p)
{
    printf("\n");
    for (int i = 0; i < 133; i++)
        printf("=");
    printf("\n%7s%16s%12s%14s%10s%10s%9s%26s\n", "Name", "ID", "Roll No", "Contact No", "Course", "SGPA", "Email", "Address");
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

    printf("\n# Student Searching Menu!\n\n");
    printf("1. Search by First name of the student\n");
    printf("2. Search by  Last name of the student\n");
    printf("3. Search by   RollNo.  of the student\n");
    printf("4. Search by   Branch   of the student\n");
    printf("5. Search by   state    of the student\n");
    printf("6. Search by   City     of the student\n");
    printf("7. Search by   SGPA     of the student\n");
    printf("8. Exit the search menu\n");

    while (choice != 8)
    {

        struct Node *temp = head;
        int flag = 0, count = 0;

        printf("\n\nEnter your choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
        {
            char fname[15];
            struct Node *fnameHead = (struct Node *)malloc(sizeof(struct Node));
            fnameHead->next = NULL;

            printf("Enter the first name of the student : ");
            scanf("%s", fname);

            while (temp != NULL)
            {

                if (strcmp(temp->Stu.name.fName, fname) == 0)
                {

                    count++;

                    if (flag == 0)
                    {

                        fnameHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        Insert(fnameHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(fnameHead);
            }
            printf("=> %d record/s found!\n", count);
            break;
        }
        case 2:
        {
            char lname[15];
            struct Node *lnameHead = (struct Node *)malloc(sizeof(struct Node));
            lnameHead->next = NULL;

            printf("Enter the last name of the student : ");
            scanf("%s", lname);

            while (temp != NULL)
            {

                if (strcmp(temp->Stu.name.lName, lname) == 0)
                {

                    count++;

                    if (flag == 0)
                    {

                        lnameHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        Insert(lnameHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(lnameHead);
            }
            printf("=> %d record/s found!\n", count);
            break;
        }
        case 3:
        {
            int rollNo = 0;
            struct Node *rollNoHead = (struct Node *)malloc(sizeof(struct Node));
            rollNoHead->next = NULL;

            printf("Enter the rollNo. of the student : ");
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

                        Insert(rollNoHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(rollNoHead);
            }
            printf("=> %d record/s found!\n", count);
            break;
        }
        case 4:
        {
            char branch[15];
            struct Node *branchHead = (struct Node *)malloc(sizeof(struct Node));
            branchHead->next = NULL;

            printf("Enter the branch of the student : ");
            scanf("%s", branch);

            while (temp != NULL)
            {

                if (strcmp(temp->Stu.Course, branch) == 0)
                {

                    count++;

                    if (flag == 0)
                    {

                        branchHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        Insert(branchHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(branchHead);
            }
            printf("=> %d record/s found!\n", count);
            break;
        }
        case 5:
        {
            char state[15];
            struct Node *stateHead = (struct Node *)malloc(sizeof(struct Node));
            stateHead->next = NULL;

            printf("Enter the state of the student : ");
            scanf("%s", state);

            while (temp != NULL)
            {

                if (strcmp(temp->Stu.address.state, state) == 0)
                {

                    count++;

                    if (flag == 0)
                    {

                        stateHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        Insert(stateHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(stateHead);
            }
            printf("=> %d record/s found!\n", count);
            break;
        }
        case 6:
        {
            char city[15];
            struct Node *cityHead = (struct Node *)malloc(sizeof(struct Node));
            cityHead->next = NULL;

            printf("Enter the city of the student : ");
            scanf("%s", city);

            while (temp != NULL)
            {

                if (strcmp(temp->Stu.address.city, city) == 0)
                {

                    count++;

                    if (flag == 0)
                    {

                        cityHead->Stu = temp->Stu;
                        flag = 1;
                    }
                    else
                    {

                        Insert(cityHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(cityHead);
            }
            printf("=> %d record/s found!\n", count);
            break;
        }
        case 7:
        {
            int SGPA = 0;
            struct Node *SGPAHead = (struct Node *)malloc(sizeof(struct Node));
            SGPAHead->next = NULL;

            printf("Enter the SGPA of the student : ");
            scanf("%d", &SGPA);

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

                        Insert(SGPAHead, temp->Stu);
                    }
                }

                temp = temp->next;
            }

            if (flag == 1)
            {

                DisplayLIST(SGPAHead);
            }
            printf("=> %d record/s found!\n", count);
            break;
        }
        case 8:
            printf("=> Successfully exited!\n");
            break;

        default:
            printf("=> Invalid input!, please enter a number between 1 to 8\n");
            break;
        }
    }
}

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
        //printList(*head_ref);
        //printf("\n%s,%s is %d\n",t->Stu.stuId,student.stuId,strcmp(t->Stu.stuId,student.stuId));
        t = t->next;
    }
    //printf("\n");
    //
    new_node->next = t->next;
    t->next = new_node;
}

struct Node *getUnion(struct Node *head1,
                      struct Node *head2)
{
    struct Node *result = NULL;
    struct Node *t1 = head1, *t2 = head2;

    while (t1 != NULL)
    {
        push(&result, t1->Stu);
        //printf("%s",t1->Stu.stuId);
        t1 = t1->next;
    }

    while (t2 != NULL)
    {
        if (!isPresent(result, t2->Stu.stuId))
            push(&result, t2->Stu);

        //printf("%s",t2->Stu.stuId);
        t2 = t2->next;
    }

    return result;
}

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

void printList(struct Node *node);

struct Student
makeStudent(char fname[], char lname[], int rollNo, char hNumber[], char city[], char state[], char email[],
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

    return newStudent;
}

void p(char message[]) { printf("%s", message); }

void UpdateUsingStuID(struct Node *head)
{
    char key[10];
    struct Node *p = head;
    int choice = 0;

    printf("Enter Student ID: ");
    scanf("%s", key);

    if (isPresent(head, key) == 0)
    {
        printf("\nThis Student ID do not exist.\n");
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
        printf("Select from menu:\n1. Update Name\n2. Update Roll No\n3. Update Contact No\n4. Update Email\n5. Update Course\n6. Update Address\n7. Update SGPA\n8. Exit \n");
        while (choice != 8)
        {
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
            {
                printf("\nEnter the new first name: ");
                scanf("%s", p->Stu.name.fName);
                printf("Enter the new last name: ");
                scanf("%s", p->Stu.name.lName);
                printf("=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 2:
            {
                printf("\nEnter the new Roll no: ");
                scanf("%d", &p->Stu.rollNo);
                printf("=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 3:
            {
                printf("\nEnter new Contact Number: ");
                scanf("%lld", &p->Stu.ContactNum);
                printf("=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 4:
            {
                printf("\nEnter new Email: ");
                scanf("%s", p->Stu.email);
                printf("=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 5:
            {
                printf("\nEnter new Course: ");
                scanf("%s", p->Stu.Course);
                printf("=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 6:
            {
                printf("\nEnter the new House number: ");
                scanf("%s", p->Stu.address.hNumber);
                printf("Enter the new City: ");
                scanf("%s", p->Stu.address.city);
                printf("Enter the new State: ");
                scanf("%s", p->Stu.address.state);
                printf("=> UPDATED SUCCESSFULLY.\n\n");
            }
            break;
            case 7: {
                printf("\nEnter the new SGPA: ");
                scanf("%f", &p->Stu.SGPA);
            }
            case 8:
            {
                updateToFile();
                printf("=> Successfully exited!\n\n");
                break;
            }
            break;
            default:
                printf("=> Invalid input! please enter a number between 1 to 6\n\n");
                break;
            }
        }
    }
}

void Message()
{
    printf("\n\n\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############   Student Record Management System Project in C   ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n\n");
}

int main()
{

    struct Student S[15];

    S[0] = makeStudent("Harry", "potter", 734, "45 aveneue street", "Manhatten", "Gujarat", "harry@gmail.com", 9.2, 33278787, "ECE");
    S[1] = makeStudent("Oliver", "wood", 14, "45 aveneue street", "Rajkot", "Gujarat", "me@gmail.com", 8.8f, 1234567899, "ECE");
    S[2] = makeStudent("Ron", "whisley", 34, "45 aveneue street", "Surat", "Gujarat", "me@gmail.com", 5.8, 123456789, "ECE");
    S[3] = makeStudent("Micheal", "Jackson", 85, "45 aveneue street", "Manhatten", "Gujarat", "me@gmail.com", 7.8, 3232323, "CHE");
    S[4] = makeStudent("Charlie", "Whatson", 5, "45 aveneue street", "New York", "Gujarat", "me@gmail.com", 9.8, 33237472, "ME");
    S[5] = makeStudent("Peter", "Parker", 25, "45 aveneue street", "Manhatten", "Gujarat", "me@gmail.com", 2.8, 332322, "ED");
    S[6] = makeStudent("Micheal", "Jackson", 85, "45 aveneue street", "Surat", "Gujarat", "me@gmail.com", 7.8, 332, "CHE");
    S[7] = makeStudent("Charlie", "Whatson", 95, "45 aveneue street", "Manhatten", "Gujarat", "me@gmail.com", 9, 33232322, "ED");
    S[8] = makeStudent("Peter", "Parker", 11, "45 aveneue street", "Bombay", "Gujarat", "me@gmail.com", 2, 332, "ECE");
    S[9] = makeStudent("Micheal", "Jackson", 13, "45 aveneue street", "Manhatten", "Gujarat", "me@gmail.com", 7, 332, "CS");
    S[10] = makeStudent("Charlie", "Whatson", 23, "45 aveneue street", "Bombay", "Gujarat", "me@gmail.com", 9, 332, "ME");
    S[11] = makeStudent("Peter", "Parker", 27, "45 aveneue street", "Manhatten", "Gujarat", "me@gmail.com", 2, 332, "ED");
    S[12] = makeStudent("Micheal", "Jackson", 2, "45 aveneue street", "Rajkot", "Gujarat", "me@gmail.com", 7, 332, "CS");
    S[13] = makeStudent("Charlie", "Whatson", 92, "45 aveneue street", "Manhatten", "Gujarat", "me@gmail.com", 9, 332, "ME");
    S[14] = makeStudent("Peter", "Parker", 21, "45 aveneue street", "Surat", "Gujarat", "me@gmail.com", 2, 332, "CS");

    // head = create(head, S, 15);
    // updateToFile();

    head = create(head, readFromFile().Stu, readFromFile().n);

    // for (int i = 0; i < 15; i++) {

    //      Insert(head, S[i]);
    //      writeToFile();
    // }
   
    // deleteStudentRecord("ED", 25);
   
    DisplayLIST(head);

    // stuSearch(head);

    return 0;
}
