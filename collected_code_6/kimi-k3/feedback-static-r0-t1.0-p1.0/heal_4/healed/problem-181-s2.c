#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t safe_strnlen(const char* s, size_t maxlen) {
    if (s == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strs == NULL || strsSize <= 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }
    
    if (strs[0] == NULL) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }
    
    size_t min_len = safe_strnlen(strs[0], SIZE_MAX);
    for (int i = 1; i < strsSize; i++) {
        if (strs[i] == NULL) {
            min_len = 0;
            break;
        }
        size_t len = safe_strnlen(strs[i], SIZE_MAX);
        if (len < min_len) {
            min_len = len;
        }
    }
    
    size_t prefix_len = 0;
    for (size_t i = 0; i < min_len; i++) {
        char c = strs[0][i];
        int match = 1;
        for (int j = 1; j < strsSize; j++) {
            if (strs[j][i] != c) {
                match = 0;
                break;
            }
        }
        if (!match) {
            break;
        }
        prefix_len++;
    }
    
    if (prefix_len == SIZE_MAX) {
        return NULL;
    }
    
    char* result = (char*)malloc(prefix_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    if (prefix_len > 0) {
        size_t first_len = safe_strnlen(strs[0], SIZE_MAX);
        if (prefix_len <= first_len) {
            size_t i;
            for (i = 0; i < prefix_len; i++) {
                result[i] = strs[0][i];
            }
        } else {
            free(result);
            return NULL;
        }
    }
    result[prefix_len] = '\0';
    
    return result;
}

int main(void) {
    char* strs1[] = {"flower", "flow", "flight"};
    char* result1 = longestCommonPrefix(strs1, 3);
    if (result1 != NULL) {
        printf("Longest common prefix: \"%s\"\n", result1);
        free(result1);
    }
    
    char* strs2[] = {"dog", "racecar", "car"};
    char* result2 = longestCommonPrefix(strs2, 3);
    if (result2 != NULL) {
        printf("Longest common prefix: \"%s\"\n", result2);
        free(result2);
    }
    
    char* strs3[] = {"alone"};
    char* result3 = longestCommonPrefix(strs3, 1);
    if (result3 != NULL) {
        printf("Longest common prefix: \"%s\"\n", result3);
        free(result3);
    }
    
    char* result4 = longestCommonPrefix(NULL, 0);
    if (result4 != NULL) {
        printf("Longest common prefix: \"%s\"\n", result4);
        free(result4);
    }
    
    return 0;
}