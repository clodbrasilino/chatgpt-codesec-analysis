#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int areRotations(char *str1, char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int size1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int size2 = strlen(str2);
    if (size1 != size2) return 0;
    char *temp = (char *)malloc(2 * size1 + 1);
    if (temp == NULL) return 0;
    snprintf(temp, 2 * size1 + 1, "%s%s", str1, str1);
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