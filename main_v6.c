#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Name {
    char fName[15];
    char lName[15];
};

struct Address {
    char hNumber[20];
    char city[15];
    char state[15];
};

struct Student {
    struct Name name;
    int rollNo;
    struct Address address;
    char email[25];
    int ContactNum;
    int SGPA;
    char Course[15];
    char stuId[10];
};

struct Node {
    struct Student Stu;
    struct Node *next;
} *head = NULL;

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%s ", node->Stu.stuId);
        node = node->next;
    }
}

// Compares two strings
int compareStr(char *str1, char *str2) {

    int i = 0;

    while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0') {

        i++;
    }

    if (str1[i] == '\0' && str2[i] == '\0') {

        return 1;
    } else {

        return 0;
    }
}

//create LL
struct Node *create(struct Student S[], int n) {
    struct Node *t, *last;
    head = (struct Node *) malloc(sizeof(struct Node));
    head->Stu = S[0];
    head->next = NULL;
    last = head;

    for (int i = 1; i < n; i++) {
        t = (struct Node *) malloc(sizeof(struct Node));
        t->Stu = S[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
    return head;
}

// insert student nodes
void Insert(struct Node *head, struct Student Stu) {
    struct Node *t, *p;
    p = head;

    while (p->next != NULL) {
        p = p->next;
    }
    t = (struct Node *) malloc(sizeof(struct Node));
    t->Stu = Stu;
    t->next = NULL;
    p->next = t;

    printf("\n=> Insertion is succesful.\n\n");
}

// Create Students Unique ID
void createStuId(char *stuId, char *branch, int rollNo) {

    char cRollNo[4] = "";
    char aux[4];

    if(rollNo<10){
        sprintf(aux, "0%d", rollNo);
    }else{
        sprintf(aux, "%d", rollNo);
    }
    strcat(cRollNo, aux);
    strcpy(stuId, branch);
    strcat(stuId, cRollNo);
    //printf("Generated: %s\n", stuId);
}

// Counts total number of students
int stuCount() {

    struct Node *temp = head;
    int count = 0;

    while (temp != NULL) {

        count++;
        temp = temp->next;
    }

    return count;
}

// Deletes selected student record
void deleteStudentRecord(char *branch, int rollNo) {

    struct Node *prevNode = NULL, *currentNode = head;
    int nodes = stuCount(), count = 1;
    char id[10];
    createStuId(id, branch, rollNo);

    while (currentNode != NULL) {

        if (count == 1) {

            if (compareStr(currentNode->Stu.stuId, id)) {

                head = currentNode->next;
                printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                free(currentNode);
                return;
            }
        } else if (count == nodes) {

            if (compareStr(currentNode->Stu.stuId, id)) {

                printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                prevNode->next = NULL;
                free(currentNode);
                return;
            }
        } else {

            if (compareStr(currentNode->Stu.stuId, id)) {

                prevNode->next = currentNode->next;
                printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n",
                       currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
                free(currentNode);
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

void DisplayStuDetails(struct Student stu, int count) {
    printf(" (%d) ", count);
    printf(" NAME : %s %s ", stu.name.fName, stu.name.lName);
    printf(" STUDENTID : %s ", stu.stuId);
    printf(" ROLLNO. : %d ", stu.rollNo);
    printf(" ADDRESS : %s, %s , %s ", stu.address.hNumber, stu.address.city, stu.address.state);
    printf(" EMAIL : %s ", stu.email);
    printf(" CONTACTNO. : %d ", stu.ContactNum);
    printf(" SGPA : %d ", stu.SGPA);
    printf(" COURSE : %s ", stu.Course);
}

void DisplayLIST(struct Node *head) {
    struct Node *p = head;
    int count = 1;

    while (p) {
        DisplayStuDetails(p->Stu, count);
        p = p->next;
        count++;
        printf("\n\n\n");
    }
}

// Searches student records
void stuSearch(struct Node *head) {

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

    while (choice != 8) {

        struct Node *temp = head;
        int flag = 0, count = 0;

        printf("\n\nEnter your choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1: {
                char fname[15];
                struct Node *fnameHead = (struct Node *) malloc(sizeof(struct Node));
                fnameHead->next = NULL;

                printf("Enter the first name of the student : ");
                scanf("%s", fname);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.name.fName, fname)) {

                        count++;

                        if (flag == 0) {

                            fnameHead->Stu = temp->Stu;
                            flag = 1;
                        } else {

                            Insert(fnameHead, temp->Stu);
                        }
                    }

                    temp = temp->next;
                }

                if (flag == 1) {

                    DisplayLIST(fnameHead);
                }
                printf("=> %d record/s found!\n", count);
                break;
            }
            case 2: {
                char lname[15];
                struct Node *lnameHead = (struct Node *) malloc(sizeof(struct Node));
                lnameHead->next = NULL;

                printf("Enter the last name of the student : ");
                scanf("%s", lname);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.name.lName, lname)) {

                        count++;

                        if (flag == 0) {

                            lnameHead->Stu = temp->Stu;
                            flag = 1;
                        } else {

                            Insert(lnameHead, temp->Stu);
                        }
                    }

                    temp = temp->next;
                }

                if (flag == 1) {

                    DisplayLIST(lnameHead);
                }
                printf("=> %d record/s found!\n", count);
                break;
            }
            case 3: {
                int rollNo = 0;
                struct Node *rollNoHead = (struct Node *) malloc(sizeof(struct Node));
                rollNoHead->next = NULL;

                printf("Enter the rollNo. of the student : ");
                scanf("%d", &rollNo);

                while (temp != NULL) {

                    if (temp->Stu.rollNo == rollNo) {

                        count++;

                        if (flag == 0) {

                            rollNoHead->Stu = temp->Stu;
                            flag = 1;
                        } else {

                            Insert(rollNoHead, temp->Stu);
                        }
                    }

                    temp = temp->next;
                }

                if (flag == 1) {

                    DisplayLIST(rollNoHead);
                }
                printf("=> %d record/s found!\n", count);
                break;
            }
            case 4: {
                char branch[15];
                struct Node *branchHead = (struct Node *) malloc(sizeof(struct Node));
                branchHead->next = NULL;

                printf("Enter the branch of the student : ");
                scanf("%s", branch);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.Course, branch)) {

                        count++;

                        if (flag == 0) {

                            branchHead->Stu = temp->Stu;
                            flag = 1;
                        } else {

                            Insert(branchHead, temp->Stu);
                        }
                    }

                    temp = temp->next;
                }

                if (flag == 1) {

                    DisplayLIST(branchHead);
                }
                printf("=> %d record/s found!\n", count);
                break;
            }
            case 5: {
                char state[15];
                struct Node *stateHead = (struct Node *) malloc(sizeof(struct Node));
                stateHead->next = NULL;

                printf("Enter the state of the student : ");
                scanf("%s", state);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.address.state, state)) {

                        count++;

                        if (flag == 0) {

                            stateHead->Stu = temp->Stu;
                            flag = 1;
                        } else {

                            Insert(stateHead, temp->Stu);
                        }
                    }

                    temp = temp->next;
                }

                if (flag == 1) {

                    DisplayLIST(stateHead);
                }
                printf("=> %d record/s found!\n", count);
                break;
            }
            case 6: {
                char city[15];
                struct Node *cityHead = (struct Node *) malloc(sizeof(struct Node));
                cityHead->next = NULL;

                printf("Enter the city of the student : ");
                scanf("%s", city);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.address.city, city)) {

                        count++;

                        if (flag == 0) {

                            cityHead->Stu = temp->Stu;
                            flag = 1;
                        } else {

                            Insert(cityHead, temp->Stu);
                        }
                    }

                    temp = temp->next;
                }

                if (flag == 1) {

                    DisplayLIST(cityHead);
                }
                printf("=> %d record/s found!\n", count);
                break;
            }
            case 7: {
                int SGPA = 0;
                struct Node *SGPAHead = (struct Node *) malloc(sizeof(struct Node));
                SGPAHead->next = NULL;

                printf("Enter the SGPA of the student : ");
                scanf("%d", &SGPA);

                while (temp != NULL) {

                    if (temp->Stu.SGPA == SGPA) {

                        count++;

                        if (flag == 0) {

                            SGPAHead->Stu = temp->Stu;
                            flag = 1;
                        } else {

                            Insert(SGPAHead, temp->Stu);
                        }
                    }

                    temp = temp->next;
                }

                if (flag == 1) {

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

int isPresent(struct Node *head, char *stuId) {
    struct Node *t = head;
    while (t != NULL) {
        if (strcmp(t->Stu.stuId, stuId) == 0)
            return 1;
        t = t->next;
    }
    return 0;
}

void push(struct Node **head_ref, struct Student student) {
    struct Node *new_node = (struct Node *) malloc(
            sizeof(struct Node));

    new_node->Stu = student;


    // If first element or deserves to be first
    // strcmp <0 => correct order
    if(*head_ref==NULL || strcmp((*head_ref)->Stu.stuId,student.stuId)>0){
        new_node->next = (*head_ref);
        (*head_ref) = new_node;
        return;
    }

    struct Node* t = *head_ref;
    while(t->next!=NULL && strcmp(t->next->Stu.stuId,student.stuId)<0){
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
                      struct Node *head2) {
    struct Node *result = NULL;
    struct Node *t1 = head1, *t2 = head2;

    while (t1 != NULL) {
        push(&result, t1->Stu);
        //printf("%s",t1->Stu.stuId);
        t1 = t1->next;
    }

    while (t2 != NULL) {
        if (!isPresent(result, t2->Stu.stuId))
            push(&result, t2->Stu);

        //printf("%s",t2->Stu.stuId);
        t2 = t2->next;
    }

    return result;
}

struct Node *getIntersection(struct Node *head1,
                             struct Node *head2) {
    struct Node *result = NULL;
    struct Node *t1 = head1;

    while (t1 != NULL) {
        if (isPresent(head2, t1->Stu.stuId))
            push(&result, t1->Stu);
        t1 = t1->next;
    }

    return result;
}

void printList(struct Node *node);

struct Student
makeStudent(char fname[], char lname[], int rollNo, char hNumber[], char city[], char state[], char email[],
            int SGPA, int contactNum, char course[]) {
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

int main() {
    struct Student S[15];

    //first student detail.rollNo
    strcpy(S[0].name.fName, "harry");
    strcpy(S[0].name.lName, "potter");
    S[0].rollNo = 10;
    strcpy(S[0].address.hNumber, "14 aveneue street");
    strcpy(S[0].address.city, "abc");
    strcpy(S[0].address.state, "texas");
    strcpy(S[0].email, "harry@hogwarts.com");
    S[0].SGPA = 34;
    S[0].ContactNum = 987;
    strcpy(S[0].Course, "CSE");
    createStuId(S[0].stuId, S[0].Course, S[0].rollNo);

    //second student detail.
    strcpy(S[1].name.fName, "oliver");
    strcpy(S[1].name.lName, "wood");
    S[1].rollNo = 11;
    strcpy(S[1].address.hNumber, "45 aveneue street");
    strcpy(S[1].address.city, "cvx");
    strcpy(S[1].address.state, "aszts");
    strcpy(S[1].email, "oliver@hogwarts.com");
    S[1].ContactNum = 123;
    strcpy(S[1].Course, "ME");
    S[1].SGPA = 82;
    createStuId(S[1].stuId, S[1].Course, S[1].rollNo);

    create(S, 2);

    // DisplayLIST(first);
    strcpy(S[2].name.fName, "ron");
    strcpy(S[2].name.lName, "whisley");
    S[2].rollNo = 12;
    strcpy(S[2].address.hNumber, "4 street");
    strcpy(S[2].address.city, "cadsf");
    strcpy(S[2].address.state, "jfgts");
    strcpy(S[2].email, "whisley@hogwarts.com");
    S[2].ContactNum = 576;
    strcpy(S[2].Course, "CHE");
    S[2].SGPA = 42;
    createStuId(S[2].stuId, S[2].Course, S[2].rollNo);

    // printf("After insertion: \n");
    //Insert(head, S[2]);
    //DisplayLIST(head);

    //   deleteStudentRecord(S[1].Course, S[1].rollNo);

    //DisplayLIST(head);
    //stuSearch(head);
    /////////////////////////

    S[3] = makeStudent("Micheal","Jackson",34,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",7,332,"CHE");
    S[4] = makeStudent("Charlie","Whatson",5,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",9,332,"ME");
    S[5] = makeStudent("Peter","Parker",25,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",2,332,"ED");
    S[6] = makeStudent("Micheal","Jackson",85,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",7,332,"CHE");
    S[7] = makeStudent("Charlie","Whatson",95,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",9,332,"ED");
    S[8] = makeStudent("Peter","Parker",11,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",2,332,"ECE");
    S[9] = makeStudent("Micheal","Jackson",13,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",7,332,"CS");
    S[10] = makeStudent("Charlie","Whatson",23,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",9,332,"ME");
    S[11] = makeStudent("Peter","Parker",27,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",2,332,"ED");
    S[12] = makeStudent("Micheal","Jackson",2,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",7,332,"CS");
    S[13] = makeStudent("Charlie","Whatson",92,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",9,332,"ME");
    S[14] = makeStudent("Peter","Parker",21,"45 aveneue street","Manhatten","Gujarat","me@gmail.com",2,332,"CS");


    struct Student sl1[] = {S[0], S[1],S[3],S[4],S[6],S[7],S[9], S[10],S[12],S[15]};
    struct Student sl2[] = {S[1], S[2],S[4],S[5],S[9],S[8],S[11],S[13],S[14], S[15]};
    struct Node *h1 = create(sl1, 10);
    struct Node *h2 = create(sl2, 10);

     p("List 1:");
     printList(h1);
     p("\nList 2:");
     printList(h2);
    p("\nList1 U List 2:");
    printList(
            getUnion(h1, h2));
    p("\nList1 intersection List 2:");
    printList(getIntersection(h1, h2));

    return 0;
}
