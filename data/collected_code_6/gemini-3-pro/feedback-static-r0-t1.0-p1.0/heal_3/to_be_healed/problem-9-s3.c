#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findMinimumRotations(const char* str) {
    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    if (len == 0) {
        return 0;
    }

    char* concatStr = (char*)malloc(2 * len + 1);
    if (concatStr == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(concatStr, str, len);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(concatStr + len, str, len);
    concatStr[2 * len] = '\0';

    int minRotations = (int)len;

    for (size_t i = 1; i <= len; i++) {
        if (strncmp(concatStr + i, str, len) == 0) {
            minRotations = (int)i;
            break;
        }
    }

    free(concatStr);

    return minRotations;
}

int main(void) {
    const char* str1 = "abc";
    int result1 = findMinimumRotations(str1);
    printf("%d\n", result1);

    const char* str2 = "aaaa";
    int result2 = findMinimumRotations(str2);
    printf("%d\n", result2);

    const char* str3 = "abab";
    int result3 = findMinimumRotations(str3);
    printf("%d\n", result3);

    return 0;
}