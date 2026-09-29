#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_lowercase(const char* str, int* count) {
    if (!str || !count) {
        return NULL;
    }

    size_t max_allowed_len = 8192;
    size_t len = 0;

    while (len < max_allowed_len && str[len] != '\0') {
        len++;
    }

    if (len == 0 || len == max_allowed_len) {
        *count = 0;
        return NULL;
    }

    int max_parts = len + 1;
    char** result = (char**)malloc(max_parts * sizeof(char*));
    if (!result) {
        return NULL;
    }

    int part_idx = 0;
    int start_idx = 0;

    for (size_t i = 0; i <= len; i++) {
        if (islower((unsigned char)str[i]) || str[i] == '\0') {
            int part_len = i - start_idx;
            if (part_len > 0) {
                result[part_idx] = (char*)malloc((part_len + 1) * sizeof(char));
                if (!result[part_idx]) {
                    for (int j = 0; j < part_idx; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                
                for (int k = 0; k < part_len; k++) {
                    result[part_idx][k] = str[start_idx + k];
                }
                result[part_idx][part_len] = '\0';
                part_idx++;
            }
            start_idx = i + 1;
        }
    }

    *count = part_idx;
    return result;
}

int main(void) {
    const char* test_str = "HELLOwORLDtEST";
    int count = 0;
    
    char** parts = split_at_lowercase(test_str, &count);
    
    if (parts) {
        for (int i = 0; i < count; i++) {
            printf("Part %d: %s\n", i, parts[i]);
            free(parts[i]);
        }
        free(parts);
    }
    
    return 0;
}