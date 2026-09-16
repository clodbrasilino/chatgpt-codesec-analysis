#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strs == NULL || strsSize <= 0) return strdup("");
    if (strsSize == 1) return strdup(strs[0]);
    
    int minLen = strlen(strs[0]);
    for (int i = 1; i < strsSize; i++) {
        if (strs[i] == NULL) return strdup("");
        int len = strlen(strs[i]);
        if (len < minLen) minLen = len;
    }
    
    char* prefix = (char*)malloc((minLen + 1) * sizeof(char));
    if (prefix == NULL) return NULL;
    
    int pos = 0;
    for (int i = 0; i < minLen; i++) {
        char c = strs[0][i];
        for (int j = 1; j < strsSize; j++) {
            if (strs[j][i] != c) {
                prefix[pos] = '\0';
                return prefix;
            }
        }
        prefix[pos++] = c;
    }
    prefix[pos] = '\0';
    return prefix;
}

int main() {
    char* strings1[] = {"flower", "flow", "flight"};
    char* result1 = longestCommonPrefix(strings1, 3);
    printf("Test 1: %s\n", result1);
    free(result1);
    
    char* strings2[] = {"dog", "racecar", "car"};
    char* result2 = longestCommonPrefix(strings2, 3);
    printf("Test 2: %s\n", result2);
    free(result2);
    
    char* strings3[] = {"interspecies", "interstellar", "interstate"};
    char* result3 = longestCommonPrefix(strings3, 3);
    printf("Test 3: %s\n", result3);
    free(result3);
    
    char* strings4[] = {"a"};
    char* result4 = longestCommonPrefix(strings4, 1);
    printf("Test 4: %s\n", result4);
    free(result4);
    
    char* strings5[] = {"", "b"};
    char* result5 = longestCommonPrefix(strings5, 2);
    printf("Test 5: %s\n", result5);
    free(result5);
    
    return 0;
}