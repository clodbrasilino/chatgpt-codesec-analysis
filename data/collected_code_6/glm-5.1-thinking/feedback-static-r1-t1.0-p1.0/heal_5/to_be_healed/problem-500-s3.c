#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(size_t count, const char * const *list) {
    if (count > 0 && list == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    size_t *lengths = NULL;
    if (count > 0) {
        lengths = malloc(count * sizeof(size_t));
        if (lengths == NULL) {
            return NULL;
        }
    }

    size_t total_length = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t remaining = SIZE_MAX - total_length;
            if (remaining == 0) {
                free(lengths);
                return NULL;
            }
            size_t len = strnlen(list[i], remaining);
            if (len == remaining) {
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
        if (lengths[i] > 0) {
            size_t available = alloc_size - offset;
            if (lengths[i] > available) {
                free(lengths);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, list[i], lengths[i]);
            offset += lengths[i];
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