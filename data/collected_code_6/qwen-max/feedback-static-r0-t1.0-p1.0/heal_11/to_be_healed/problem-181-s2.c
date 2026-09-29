#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest_common_prefix(char **strs, int num) {
    if (num == 0) return "";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t prefix_len = strlen(strs[0]);
    for (int i = 1; i < num; ++i) {
        const char *str = strs[i];
        for (size_t j = 0; j < prefix_len; ++j) {
            if (str[j] == '\0' || strs[0][j] != str[j]) {
                prefix_len = j;
                break;
            }
        }
        if (prefix_len == 0) break;
    }

    char *prefix = malloc(prefix_len + 1);
    if (prefix == NULL) {
        return "";
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(prefix, strs[0], prefix_len);
    prefix[prefix_len] = '\0';
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