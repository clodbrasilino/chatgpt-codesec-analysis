#include <stdio.h>
#include <string.h>

int areRotations(char *str1, char *str2) {
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    if (size1 != size2) return 0;
    char *temp = (char *)malloc(2 * sizeof(str1) + 1);
    if (temp == NULL) return 0;
    strcpy(temp, str1);
    strcat(temp, str1);
    if (strstr(temp, str2) != NULL) {
        free(temp);
        return 1;
    }
    free(temp);
    return 0;
}

int main() {
    char s1[] = "abcd";
    char s2[] = "cdab";
    if (areRotations(s1, s2)) {
        printf("Given strings are rotations of each other.\n");
    } else {
        printf("Given strings are not rotations of each other.\n");
    }
    return 0;
}