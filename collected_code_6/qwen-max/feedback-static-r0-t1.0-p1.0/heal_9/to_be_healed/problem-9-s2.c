#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int minRotationRequired(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(s);
    if (n == 0) return 0;
    char *tmp = (char *)malloc(n + 1);
    if (tmp == NULL) return -1;
    int minRot = n;

    for (int i = 0; i < n; ++i) {
        size_t len1 = n - i;
        size_t len2 = i;
        memmove(tmp, s + i, len1);
        tmp[len1] = '\0';
        memmove(tmp + len1, s, len2);
        tmp[n] = '\0';

        if (strncmp(tmp, s, n) == 0) {
            minRot = i;
            break;
        }
    }

    free(tmp);
    return minRot;
}

int main() {
    const char s[] = "abcde";
    int result = minRotationRequired(s);
    printf("%d\n", result);
    return 0;
}