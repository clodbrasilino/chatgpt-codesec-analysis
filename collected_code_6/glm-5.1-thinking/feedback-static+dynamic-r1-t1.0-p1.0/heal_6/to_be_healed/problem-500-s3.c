#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(size_t count, const char * const *list) {
    if (count > 0 && list == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    size_t *lengths = NULL;

    if (count > 0) {
        lengths = malloc(count * sizeof(size_t));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t max_len = SIZE_MAX - total_length;
            size_t len = strnlen(list[i], max_len);
            if (len == max_len) {
                free(lengths);
                return NULL;
            }
            lengths[i] = len;
            total_length += len;
        } else {
            lengths[i] = 0;
        }
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    size_t alloc_size = total_length + 1;

    char *result = malloc(alloc_size);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        size_t len = lengths[i];
        if (len > 0) {
            if (offset + len >= alloc_size) {
                free(result);
                free(lengths);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }
    
    result[offset] = '\0';
    free(lengths);

    return result;
}

int main(void) {
    const char *list[] = {"Hello", ", ", "world", "!"};
    size_t count = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(count, list);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}