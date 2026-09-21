#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 0;
    size_t i;

    if (list == NULL || size == 0) {
        char *empty_str = malloc(1);
        if (empty_str == NULL) return NULL;
        empty_str[0] = '\0';
        return empty_str;
    }

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t available = SIZE_MAX - total_length;
            size_t len = strnlen(list[i], available);
            if (len == available && list[i][len] != '\0') return NULL;
            total_length += len;
        }
    }

    if (total_length == SIZE_MAX) return NULL;

    char *result = malloc(total_length + 1);
    if (result == NULL) return NULL;

    char *ptr = result;
    size_t remaining = total_length + 1;

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t available = remaining > 0 ? remaining - 1 : 0;
            size_t len = strnlen(list[i], available);
            if (len > available) {
                free(result);
                return NULL;
            }
            if (len > 0) {
                if (len <= remaining) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(ptr, list[i], len);
                } else {
                    free(result);
                    return NULL;
                }
            }
            ptr += len;
            remaining -= len;
        }
    }

    *ptr = '\0';

    return result;
}

int main(void) {
    char *list[] = {"Hello", ", ", "world", "!"};
    size_t size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    return 0;
}