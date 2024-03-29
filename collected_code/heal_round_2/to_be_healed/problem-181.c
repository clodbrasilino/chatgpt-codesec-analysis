#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int size) {
    if (size == 0) {
        return "";
    }
    
    char* prefix = strdup(strs[0]);
    int i, j;
    
    for (i = 1; i < size; i++) {
        j = 0;
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'prefix' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        while (prefix[j] && strs[i][j] && prefix[j] == strs[i][j]) {
            j++;
        }
        
        prefix[j] = '\0';
    }
    
    return prefix;
}

int main() {
    char* strings[] = {"apple", "application", "app", "aptitude"};
    int size = sizeof(strings) / sizeof(strings[0]);
    
    char* commonPrefix = longestCommonPrefix(strings, size);
    
    printf("Longest common prefix: %s\n", commonPrefix);
    
    free(commonPrefix);
    
    return 0;
}