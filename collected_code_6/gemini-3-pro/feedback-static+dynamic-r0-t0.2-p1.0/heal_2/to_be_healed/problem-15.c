#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_lowercase(const char* str, int* count) {
    if (!str || !count) {
        return NULL;
    }

    int max_splits = 1;
    const char* p = str;
    while (*p != '\0') {
        if (islower((unsigned char)*p)) {
            max_splits++;
        }
        p++;
    }

    char** result = (char**)malloc(max_splits * sizeof(char*));
    if (!result) {
        return NULL;
    }

    int current_split = 0;
    const char* start = str;
    p = str;

    while (1) {
        if (islower((unsigned char)*p) || *p == '\0') {
            size_t sub_len = p - start;
            if (sub_len > 0) {
                result[current_split] = (char*)malloc((sub_len + 1) * sizeof(char));
                if (!result[current_split]) {
                    for (int j = 0; j < current_split; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[current_split], start, sub_len);
                result[current_split][sub_len] = '\0';
                current_split++;
            }
            if (*p == '\0') {
                break;
            }
            start = p + 1;
        }
        p++;
    }

    *count = current_split;
    return result;
}

int main(void) {
    const char* test_str = "HELLOwORLDtHISiSaTEST";
    int count = 0;
    
    char** splits = split_at_lowercase(test_str, &count);
    
    if (splits) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", splits[i]);
            free(splits[i]);
        }
        free(splits);
    }
    
    return 0;
}