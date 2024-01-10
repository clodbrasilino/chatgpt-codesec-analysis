#include <stdio.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int size) {
    if (size == 0) {
        return "";
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'strs[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    char* prefix = strs[0];
    int i, j;
    
    for (i = 1; i < size; i++) {
        j = 0;
        /* Possible weaknesses found:
         *  Cannot determine that 'strs[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        while (prefix[j] && strs[i][j] && prefix[j] == strs[i][j]) {
            j++;
        }
        
        /* Possible weaknesses found:
         *  write to string literal [-Wanalyzer-write-to-string-literal]
         *  Cannot determine that 'prefix' is initialized [premium-bughuntingUninit]
         */
        prefix[j] = '\0';
    }
    
    return prefix;
}

int main() {
    char* strings[] = {"apple", "application", "app", "aptitude"};
    int size = sizeof(strings) / sizeof(strings[0]);
    
    char* commonPrefix = longestCommonPrefix(strings, size);
    
    printf("Longest common prefix: %s\n", commonPrefix);
    
    return 0;
}