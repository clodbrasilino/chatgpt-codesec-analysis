#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char* str, size_t n) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0 || n == 0 || n % len == 0) {
        return;
    }

    n = n % len;
    
    char* temp = (char*)malloc((n + 1) * sizeof(char));
    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, str, n);
    temp[n] = '\0';

    memmove(str, str + n, len - n);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str + len - n, temp, n);

    free(temp);
}

int main(void) {
    char str[] = "HelloWorld";
    size_t rotations = 3;

    leftRotateString(str, rotations);
    printf("%s\n", str);

    return 0;
}