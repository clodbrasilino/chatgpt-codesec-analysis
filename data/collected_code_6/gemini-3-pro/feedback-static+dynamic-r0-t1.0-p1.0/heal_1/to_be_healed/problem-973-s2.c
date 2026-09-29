#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char *str, size_t d) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0 || d == 0) {
        return;
    }

    d = d % len;
    if (d == 0) {
        return;
    }

    char *temp = (char *)malloc((d + 1) * sizeof(char));
    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, str, d);
    temp[d] = '\0';

    memmove(str, str + d, len - d);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str + len - d, temp, d);

    free(temp);
}

int main() {
    char str[] = "HelloWorld";
    size_t d = 3;

    leftRotateString(str, d);
    printf("%s\n", str);

    return 0;
}