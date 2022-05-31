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
  int ContactNum;
  int SGPA;
  char Course[15];
  char stuId[10];
};

struct Node
{
  struct Student Stu;
  struct Node *next;
} *head = NULL;

// Compares two strings
int compareStr(char *str1, char *str2)
{

  int i = 0;

  while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
  {

    i++;
  }

  if (str1[i] == '\0' && str2[i] == '\0')
  {

    return 1;
  }
  else
  {

    return 0;
  }
}

//create LL
void create(struct Student S[], int n)
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
}
// insert student nodes
void Insert(struct Node* head, struct Student Stu)
{
  struct Node *t, *p;
  p = head;

  while (p->next != NULL)
  {
    p = p->next;
  }
  t = (struct Node *)malloc(sizeof(struct Node));
  t->Stu = Stu;
  t->next = NULL;
  p->next = t;

  printf("\n# Insertion is succesful.\n\n");
}

// Create Students Unique ID
void createStuId(char *stuId, char *branch, int rollNo)
{

  char cRollNo[3] = {'0'};
  char aux[3];

  sprintf(aux, "%d", rollNo);
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

// Deletes selected student record
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

      if (compareStr(currentNode->Stu.stuId, id))
      {

        head = currentNode->next;
        printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n", currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
        free(currentNode);
        return;
      }
    }
    else if (count == nodes)
    {

      if (compareStr(currentNode->Stu.stuId, id))
      {

        printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n", currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
        prevNode->next = NULL;
        free(currentNode);
        return;
      }
    }
    else
    {

      if (compareStr(currentNode->Stu.stuId, id))
      {

        prevNode->next = currentNode->next;
        printf("=> Student record of Name: \"%s %s\" and StudentID: \"%s\" got successfully deleted!\n\n", currentNode->Stu.name.fName, currentNode->Stu.name.lName, currentNode->Stu.stuId);
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

void DisplayStuDetails(struct Student stu)
{
  printf("Name : %s %s", stu.name.fName, stu.name.lName);
  printf("\nStudent ID : %s", stu.stuId);
  printf("\nRoll no : %d", stu.rollNo);
  printf("\nAddress: %s, %s , %s", stu.address.hNumber, stu.address.city, stu.address.state);
  printf("\nEmail: %s", stu.email);
  printf("\nContact Number: %d", stu.ContactNum);
  printf("\nSGPA: %d ", stu.SGPA);
  printf("\nCourse: %s", stu.Course);
}

void DisplayLIST(struct Node* head)
{
  struct Node *p = head;

  while (p)
  {
    DisplayStuDetails(p->Stu);
    p = p->next;
    printf("\n\n\n");
  }
}

int main()
{
  struct Student S[5];

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
  Insert(head, S[2]);
  DisplayLIST(head);

  deleteStudentRecord(S[1].Course, S[1].rollNo);

  DisplayLIST(head);

  return 0;
}
