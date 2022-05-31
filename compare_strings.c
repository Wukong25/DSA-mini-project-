#include <stdio.h>

int compareStr(char* str1, char* str2) {

    int i = 0;

    while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0') {

        i++;
    }

    if (str1[i] == '\0' && str2[i] == '\0') {

        return 1;
    }
    else {

        return 0;
    }
}

int main() {

    char str1[] = "Harshvardhan";
    char str2[] = "Harshvardhan";
    char str3[] = "Sun Wukong";

    if (compareStr(str3, str3)) {

        printf("Both are  equal\n");
    }
    else {

        printf("Both are not equal\n");
    }
    return 0;
}