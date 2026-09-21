#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char* str, size_t n) {
    if (str == NULL) {
        return;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0 || n == 0 || n % len == 0) {
        return;
    }

    n = n % len;
    
    char* temp = (char*)malloc(n * sizeof(char));
    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, n);

    memmove(str, str + n, len - n);
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + len - n, temp, n);

    free(temp);
}

int main(void) {
    char str[] = "HelloWorld";
    size_t rotations = 3;

    leftRotateString(str, rotations);
    printf("%s\n", str);

    return 0;
}