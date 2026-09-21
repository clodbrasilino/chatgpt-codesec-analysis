#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *search_pattern(const char *text, const char *pattern, int *position) {
    if (text == NULL || pattern == NULL || position == NULL) {
        return NULL;
    }
    
    size_t text_len = safe_strlen(text, SIZE_MAX);
    size_t pattern_len = safe_strlen(pattern, SIZE_MAX);
    
    if (text_len > SIZE_MAX / 2) {
        return NULL;
    }
    
    if (pattern_len == 0) {
        *position = 0;
        return (char *)text;
    }
    
    if (pattern_len > text_len) {
        return NULL;
    }
    
    for (size_t i = 0; i <= text_len - pattern_len; i++) {
        size_t j;
        for (j = 0; j < pattern_len; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        
        if (j == pattern_len) {
            *position = (int)i;
            return (char *)(text + i);
        }
    }
    
    return NULL;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown";
    int position = -1;
    char *result = search_pattern(text, pattern, &position);
    
    if (result != NULL) {
        printf("Pattern found at position %d: %s\n", position, result);
    } else {
        printf("Pattern not found\n");
    }
    
    const char *pattern2 = "cat";
    int position2 = -1;
    char *result2 = search_pattern(text, pattern2, &position2);
    
    if (result2 != NULL) {
        printf("Pattern found at position %d: %s\n", position2, result2);
    } else {
        printf("Pattern not found\n");
    }
    
    const char *empty_pattern = "";
    int position3 = -1;
    const char *result3 = search_pattern(text, empty_pattern, &position3);
    
    if (result3 != NULL) {
        printf("Empty pattern found at position %d\n", position3);
    } else {
        printf("Empty pattern not found\n");
    }
    
    return 0;
}