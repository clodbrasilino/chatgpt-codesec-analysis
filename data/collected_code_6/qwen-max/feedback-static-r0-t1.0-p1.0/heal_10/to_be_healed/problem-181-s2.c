#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest_common_prefix(char **strs, int num) {
    if (num == 0) return "";

    char *prefix = strs[0];
    for (int i = 1; i < num; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t prefix_len = strlen(prefix);
        const char *str = strs[i];
        for (size_t j = 0; j < prefix_len; ++j) {
            if (str[j] == '\0' || prefix[j] != str[j]) {
                prefix[j] = '\0';
                break;
            }
        }
        if (*prefix == '\0') break;
    }
    return prefix;
}

int main() {
    char *strs[] = {"flower", "flow", "flight"};
    int num = 3;
    char *result = longest_common_prefix(strs, num);
    printf("%s\n", result);
    return 0;
}