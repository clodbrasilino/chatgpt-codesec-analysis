#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest_common_prefix(char **strs, int num) {
    if (num == 0) return "";

    char *prefix = strs[0];
    size_t len = strlen(prefix);
    
    for (int i = 1; i < num; ++i) {
        size_t j;
        for (j = 0; j < len && strs[i][j] != '\0' && prefix[j] == strs[i][j]; ++j);
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
    return 0;
}