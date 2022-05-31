#include "main_ver-2.c"

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

// Searches student records
void stuSearch(struct Node* head) {

    int choice = 1;

    printf("\n# Student Searching Menu!\n\n");
    printf("1. Search by First name of the student\n");
    printf("2. Search by Last name of the student\n");
    printf("3. Search by RollNo. of the student\n");
    printf("4. Search by Branch of the student\n");
    printf("5. Search by state of the student\n");
    printf("6. Search by City of the student\n");
    printf("7. Search by SGPA of the student\n");
    printf("8. Exit the search menu\n");
    
    while (choice != 8) {

        struct Node* temp = head;
        int flag = 0, count = 0;

        printf("\n\nEnter your choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {

            case 1:
                char fname[15];
                struct Node* fnameHead = (struct Node*) malloc(sizeof(struct Node));
                fnameHead->next = NULL;

                printf("Enter the first name of the student : ");
                scanf("%s", fname);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.name.fName, fname)) {

                        count++;

                        if (flag == 0) {

                            fnameHead->Stu = temp->Stu;
                            flag = 1;
                        }
                        else {

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

            case 2:
                char lname[15];
                struct Node* lnameHead = (struct Node*) malloc(sizeof(struct Node));
                lnameHead->next = NULL;

                printf("Enter the last name of the student : ");
                scanf("%s", lname);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.name.lName, lname)) {

                        count++;

                        if (flag == 0) {

                            lnameHead->Stu = temp->Stu;
                            flag = 1;
                        }
                        else {

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

            case 3:
                int rollNo = 0;
                struct Node* rollNoHead = (struct Node*) malloc(sizeof(struct Node));
                rollNoHead->next = NULL;

                printf("Enter the rollNo. of the student : ");
                scanf("%d", &rollNo);

                while (temp != NULL) {

                    if (temp->Stu.rollNo == rollNo) {

                        count++;

                        if (flag == 0) {

                            rollNoHead->Stu = temp->Stu;
                            flag = 1;
                        }
                        else {

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

            case 4:
                char branch[15];
                struct Node* branchHead = (struct Node*) malloc(sizeof(struct Node));
                branchHead->next = NULL;

                printf("Enter the branch of the student : ");
                scanf("%s", branch);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.Course, branch)) {

                        count++;

                        if (flag == 0) {

                            branchHead->Stu = temp->Stu;
                            flag = 1;
                        }
                        else {

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

            case 5:
                char state[15];
                struct Node* stateHead = (struct Node*) malloc(sizeof(struct Node));
                stateHead->next = NULL;

                printf("Enter the state of the student : ");
                scanf("%s", state);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.address.state, state)) {

                        count++;

                        if (flag == 0) {

                            stateHead->Stu = temp->Stu;
                            flag = 1;
                        }
                        else {

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

            case 6:
                char city[15];
                struct Node* cityHead = (struct Node*) malloc(sizeof(struct Node));
                cityHead->next = NULL;

                printf("Enter the city of the student : ");
                scanf("%s", city);

                while (temp != NULL) {

                    if (compareStr(temp->Stu.address.city, city)) {

                        count++;

                        if (flag == 0) {

                            cityHead->Stu = temp->Stu;
                            flag = 1;
                        }
                        else {

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

            case 7:
                int SGPA = 0;
                struct Node* SGPAHead = (struct Node*) malloc(sizeof(struct Node));
                SGPAHead->next = NULL;

                printf("Enter the SGPA of the student : ");
                scanf("%d", &SGPA);

                while (temp != NULL) {

                    if (temp->Stu.SGPA == SGPA) {

                        count++;

                        if (flag == 0) {

                            SGPAHead->Stu = temp->Stu;
                            flag = 1;
                        }
                        else {

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

            case 8:
                printf("=> Successfully exited!\n");
                break;

            default:
                printf("=> Invalid input!, please enter a number between 1 to 8\n");
                break;

        }
    }
}