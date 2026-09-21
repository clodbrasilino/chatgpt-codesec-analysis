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
    int len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char* concatStr = (char*)malloc(2 * len + 1);
    if (concatStr == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(concatStr, str);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(concatStr, str);

    int minRotations = len;

    for (int i = 1; i <= len; i++) {
        if (strncmp(concatStr + i, str, len) == 0) {
            minRotations = i;
            break;
        }
    }

    free(concatStr);
    concatStr = NULL;

    return minRotations == len ? len : minRotations;
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