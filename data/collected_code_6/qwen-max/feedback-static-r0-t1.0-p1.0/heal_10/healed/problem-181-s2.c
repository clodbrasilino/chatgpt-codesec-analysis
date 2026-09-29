#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest_common_prefix(char **strs, int num) {
    if (num == 0) return "";

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