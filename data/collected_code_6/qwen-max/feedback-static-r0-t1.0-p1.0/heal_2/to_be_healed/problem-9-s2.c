#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int minRotationRequired(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(s);
    char *tmp = (char *)malloc(n + 1);
    if (tmp == NULL) return -1;
    int minRot = n;
    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(tmp, s + i, n - i);
        tmp[n - i] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(tmp, s, i);
        tmp[n] = '\0';
        if (strcmp(tmp, s) == 0) {
            minRot = i;
            break;
        }
    }
    free(tmp);
    return minRot;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 's' can be declared as const array [constVariable]
     */
    char s[] = "abcde";
    int result = minRotationRequired(s);
    printf("%d\n", result);
    return 0;
}