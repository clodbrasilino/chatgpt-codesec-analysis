#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int areRotations(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        return 0;
    }

    char *temp = (char *)malloc(2 * len1 + 1);
    if (temp == NULL) {
        return 0;
    }

    strcpy(temp, str1);
    strcat(temp, str1);

    int result = (strstr(temp, str2) != NULL);

    free(temp);
    return result;
}

int main(void) {
    char str1[100], str2[100];

    printf("Enter first string: ");
    if (scanf("%99s", str1) != 1) {
        return 1;
    }

    printf("Enter second string: ");
    if (scanf("%99s", str2) != 1) {
        return 1;
    }

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }

    return 0;
}