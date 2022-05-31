#include "main_v9.05.c"

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

    if (fread == 0)
    {

        printf("\n=> Error reading file!\n");
    }

    fclose(ptr);

    createInfo.Stu = stu;
    createInfo.n = i;

    return createInfo;
}

// Updates student record in the file
void UpdateToFile() {

    struct Node* temp = head;
    FILE* ptr = fopen("student_record.dat", "w");

    if (ptr == NULL) {

        printf("\nError file opening!\n");
    }

    while (temp != NULL) {

        fwrite(&temp->Stu, sizeof(struct Node), 1, ptr);
        temp = temp->next;
    }

    if (fwrite == NULL) {

        printf("\nError writing file!\n");
    }

    fclose(ptr);
}

