#include <stdio.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) return "";
    for (int idx = 0; idx < strlen(strs[0]); idx++) {
        char c = strs[0][idx];
        for (int i = 1; i < strsSize; i++) {
            if (idx == strlen(strs[i]) || strs[i][idx] != c)
                return strndup(strs[0], idx);
        }
    }
    return strs[0];
}

int main() {
    char* strs[] = {"flower","flow","flight"};
    int strsSize = sizeof(strs) / sizeof(char*);
    char* lcp = longestCommonPrefix(strs, strsSize);
    printf("Longest common prefix: %s\n", lcp);
    return 0;
}