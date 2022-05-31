// modifies existing student record
void modify(char* key) {

struct Node *p = head;

    while (p)
        {

            if (strcmp(p->Stu.stuId, key) == 0)
            {
                break;
            }

            p = p->next;
        }

        scanf("%s", p->Stu.name.fName);
        scanf("%s", p->Stu.name.lName);
        scanf("%lld", &p->Stu.ContactNum);
        scanf("%s", p->Stu.email);
        scanf("%s", p->Stu.address.hNumber);
        scanf("%s", p->Stu.address.city);
        scanf("%s", p->Stu.address.state);
        scanf("%f", &p->Stu.SGPA);
}