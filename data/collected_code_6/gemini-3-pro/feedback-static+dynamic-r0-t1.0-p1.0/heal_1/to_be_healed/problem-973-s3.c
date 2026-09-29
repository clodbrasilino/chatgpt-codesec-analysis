#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leftRotateString(char *str, size_t rotations) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0 || rotations == 0 || rotations % len == 0) {
        return;
    }

    rotations = rotations % len;

    char *temp = (char *)malloc(rotations + 1);
    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, str, rotations);
    temp[rotations] = '\0';

    memmove(str, str + rotations, len - rotations);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str + len - rotations, temp, rotations);

    free(temp);
}

int main(void) {
    char str[] = "Hello, World!";
    size_t rotations = 7;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}