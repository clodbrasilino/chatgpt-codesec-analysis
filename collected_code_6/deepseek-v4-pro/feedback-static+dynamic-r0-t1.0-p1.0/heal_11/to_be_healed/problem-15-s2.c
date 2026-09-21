#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, int *count) {
    if (!str || !count) {
        if (count) *count = 0;
        return NULL;
    }
    
    size_t len = strnlen(str, 4096);
    if (len == 0 || len > 4095) {
        *count = 0;
        return NULL;
    }
    
    size_t max_parts = len + 1;
    char **parts = (char **)calloc(max_parts, sizeof(char *));
    if (!parts) {
        *count = 0;
        return NULL;
    }
    
    size_t part_count = 0;
    size_t start = 0;
    
    for (size_t i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            size_t part_len = i - start;
            if (part_len > 0) {
                if (part_count >= max_parts) {
                    for (size_t j = 0; j < part_count; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    *count = 0;
                    return NULL;
                }
                
                if (part_len > len - start) {
                    part_len = len - start;
                }
                
                if (part_len > 4096) {
                    for (size_t j = 0; j < part_count; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    *count = 0;
                    return NULL;
                }
                
                char *part = (char *)malloc(part_len + 1);
                if (!part) {
                    for (size_t j = 0; j < part_count; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    *count = 0;
                    return NULL;
                }
                
                if (part_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(part, str + start, part_len);
                }
                part[part_len] = '\0';
                
                parts[part_count] = part;
                part_count++;
            }
            start = i + 1;
        }
    }
    
    *count = (int)part_count;
    if (part_count == 0) {
        free(parts);
        return NULL;
    }
    
    return parts;
}

void free_split_result(char **parts, int count) {
    if (!parts) return;
    for (int i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    int count = 0;
    
    char **result = split_at_lowercase(test_string, &count);
    if (result) {
        printf("Split into %d parts:\n", count);
        for (int i = 0; i < count; i++) {
            printf("[%d]: '%s'\n", i, result[i]);
        }
        free_split_result(result, count);
    } else {
        printf("No parts or error occurred (count=%d)\n", count);
    }
    
    return 0;
}