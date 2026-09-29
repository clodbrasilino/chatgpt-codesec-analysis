#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char *str, size_t d) {
    if (str == NULL) {
        return;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

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
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, d);
    temp[d] = '\0';

    memmove(str, str + d, len - d);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + len - d, temp, d);
    str[len] = '\0';

    free(temp);
}

int main() {
    char str[] = "HelloWorld";
    size_t d = 3;

    leftRotateString(str, d);
    printf("%s\n", str);

    return 0;
}