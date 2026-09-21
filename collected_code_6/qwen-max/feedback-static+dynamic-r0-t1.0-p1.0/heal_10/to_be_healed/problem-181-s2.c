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
    snprintf(prefix, len + 1, "%s", strs[0]);

    for (int i = 1; i < num; ++i) {
        size_t j;
        for (j = 0; j < len && prefix[j] == strs[i][j]; ++j);
        if (j == 0) break;
        prefix[j] = '\0';
        len = j;
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