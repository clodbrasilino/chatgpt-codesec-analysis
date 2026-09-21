#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate(char *str, int d) {
    if (str == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    if (n == 0) return;

    d = (d % n + n) % n;
    if (d <= 0) return;

    char *temp = malloc(d + 1);
    if (temp == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, d);
    temp[d] = '\0';
    memmove(str, str + d, n - d + 1);
    /* Possible weaknesses found:
     * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
     */
    strncat(str, temp, d);

    free(temp);
}

int main() {
    char str[] = "abcdef";
    int d = 2;
    left_rotate(str, d);
    printf("%s\n", str);
    return 0;
}