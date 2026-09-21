#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_lowercase(const char* str, int* count) {
    if (!str || !count) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Assignment 'max_allowed_len=8192', assigned value is 8192
     */
    size_t max_allowed_len = 8192;
    /* Possible weaknesses found:
     *  Either the condition 'len==max_allowed_len' is redundant or the array 'str[15]' is accessed at index 8192, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     *  Array index out of bounds
     */
    while (str[len] != '\0' && len < max_allowed_len) {
        len++;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'len==max_allowed_len' is not redundant
     */
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
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[part_idx], str + start_idx, part_len);
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