#include "main.c"

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

void delete (char *branch, int rollNo)
{

    struct Node *prevNode = NULL, *currentNode = head;
    int nodes = stuCount(), count = 1;
    char id[10];
    createStuId(id, branch, rollNo);

    while (currentNode != NULL)
    {

        if (count == 1)
        {

            if (currentNode->Stu.stuId == id)
            {

                head = currentNode->next;
                printf("Student record of %s got successfully deleted!", currentNode->Stu.stuId);
                free(currentNode);
                return;
            }
        }
        else if (count == nodes)
        {

            if (currentNode->Stu.stuId == id)
            {

                printf("Student record of %s got successfully deleted!", currentNode->Stu.stuId);
                free(currentNode);
                return;
            }
        }
        else
        {

            if (currentNode->Stu.stuId == id)
            {

                prevNode->next = currentNode->next;
                printf("Student record of %s got successfully deleted!", currentNode->Stu.stuId);
                free(currentNode);
                return;
            }
        }

        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    printf("Student record %s didn't found!", currentNode->Stu.stuId);
    return;
}
