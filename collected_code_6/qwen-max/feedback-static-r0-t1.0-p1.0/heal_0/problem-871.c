#include <stdio.h>
#include <string.h>

int areRotations(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        return 0;
    }

    char temp[2 * len1 + 1];
    strcpy(temp, str1);
    strcat(temp, str1);

    return strstr(temp, str2) != NULL;
}

int main() {
    char str1[] = "waterbottle";
    char str2[] = "erbottlewat";

    if (areRotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}