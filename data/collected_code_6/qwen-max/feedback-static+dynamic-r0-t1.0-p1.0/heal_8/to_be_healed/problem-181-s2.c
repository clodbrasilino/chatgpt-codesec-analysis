#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest_common_prefix(char **strs, int num) {
    if (num == 0) return "";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(strs[0]);
    char *prefix = (char *)malloc(len + 1);
    if (prefix == NULL) exit(1);
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(prefix, strs[0]);

    for (int i = 1; i < num; ++i) {
        size_t j;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        for (j = 0; j < len && j < strlen(strs[i]) && prefix[j] == strs[i][j]; ++j);
        prefix[j] = '\0';
        len = j;
        if (len == 0) break;
    }
    return prefix;
}

int main() {
    char *strs[] = {"flower", "flow", "flight"};
    int num = 3;
    char *result = longest_common_prefix(strs, num);
    printf("%s\n", result);
    free(result);
    return 0;
}