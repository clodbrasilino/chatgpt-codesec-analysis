#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (n > 0 && len > 1) {
        n = n % len;
        char *temp = malloc(n + 1);
        if (temp == NULL) return;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str, n);
        temp[n] = '\0';
        memmove(str, str + n, len - n + 1);
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(str, temp, n);
        free(temp);
    }
}

int main() {
    char str[] = "HelloWorld";
    int n = 3;
    left_rotate_string(str, n);
    printf("%s\n", str);
    return 0;
}