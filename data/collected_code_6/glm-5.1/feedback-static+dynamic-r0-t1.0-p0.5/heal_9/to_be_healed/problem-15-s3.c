#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, size_t *count) {
    size_t capacity = 16;
    size_t idx = 0;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    const char *start = str;
    while (*start) {
        const char *end = start;
        while (*end && !islower((unsigned char)*end)) {
            end++;
        }

        size_t token_len = end - start;
        if (token_len > 0) {
            if (idx >= capacity) {
                capacity *= 2;
                char **new_result = realloc(result, capacity * sizeof(char *));
                if (new_result == NULL) {
                    for (size_t i = 0; i < idx; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                result = new_result;
            }

            size_t alloc_size = token_len + 1;
            char *token = malloc(alloc_size);
            if (token == NULL) {
                for (size_t i = 0; i < idx; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(token, start, alloc_size);
            result[idx++] = token;
        }

        if (*end) {
            start = end + 1;
        } else {
            start = end;
        }
    }

    *count = idx;
    return result;
}

int main(void) {
    const char *input = "ABCdefGHIjklMNO";
    size_t count = 0;
    char **parts = split_at_lowercase(input, &count);

    if (parts != NULL) {
        for (size_t i = 0; i < count; i++) {
            /* Possible weaknesses found:
             * ASan: heap-buffer-overflow
             */
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    }

    return 0;
}