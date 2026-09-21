#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 65536

char** split_at_lowercase(const char* input, int* count) {
    if (input == NULL || count == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (input[len] != '\0' && len < MAX_INPUT_LENGTH) {
        len++;
    }

    if (len == 0) {
        *count = 0;
        return NULL;
    }

    int part_count = 1;
    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)input[i])) {
            part_count++;
        }
    }

    char** result = (char**)malloc(part_count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int current_part = 0;
    size_t start_idx = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)input[i])) {
            size_t part_len = i - start_idx;
            result[current_part] = (char*)malloc((part_len + 1) * sizeof(char));
            if (result[current_part] == NULL) {
                for (int j = 0; j < current_part; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[current_part], input + start_idx, part_len);
            result[current_part][part_len] = '\0';
            current_part++;
            start_idx = i + 1;
        }
    }

    size_t part_len = len - start_idx;
    result[current_part] = (char*)malloc((part_len + 1) * sizeof(char));
    if (result[current_part] == NULL) {
        for (int j = 0; j < current_part; j++) {
            free(result[j]);
        }
        free(result);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result[current_part], input + start_idx, part_len);
    result[current_part][part_len] = '\0';
    
    *count = part_count;
    return result;
}

void free_split_result(char** result, int count) {
    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int main(void) {
    const char* test_str = "HELLOwWORLDtTEST";
    int count = 0;
    
    char** parts = split_at_lowercase(test_str, &count);
    
    if (parts != NULL) {
        for (int i = 0; i < count; i++) {
            printf("Part %d: %s\n", i, parts[i]);
        }
        free_split_result(parts, count);
    } else {
        printf("Memory allocation failed or empty string.\n");
    }

    return 0;
}