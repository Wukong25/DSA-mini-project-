#include <stdio.h>

int main() {

    FILE *file1 = fopen("/home/sun_wukong/Downloads/mytxt.txt", "a" );

    int i = 0;
    char str[1000];

    printf("Write any thing : ");
    fgets(str, 1000, stdin);

    fprintf(file1, str);

    return 0;
}