#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    const char **elements;
    size_t count;
} Tuple;

static size_t bounded_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static bool safe_add_size(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return false;
    }
    *result = a + b;
    return true;
}

char *concatenate_tuple(const Tuple *tuple, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple->elements == NULL || tuple->count == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delimiter_length = bounded_strlen(delimiter, 4096);
    size_t i;

    if (delimiter_length == 4096 && delimiter[4095] != '\0') {
        return NULL;
    }

    for (i = 0; i < tuple->count; i++) {
        if (tuple->elements[i] == NULL) {
            return NULL;
        }
        size_t element_length = bounded_strlen(tuple->elements[i], 4096);
        if (element_length == 4096 && tuple->elements[i][4095] != '\0') {
            return NULL;
        }
        if (!safe_add_size(total_length, element_length, &total_length)) {
            return NULL;
        }
        if (i < tuple->count - 1) {
            if (!safe_add_size(total_length, delimiter_length, &total_length)) {
                return NULL;
            }
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (i = 0; i < tuple->count; i++) {
        size_t element_length = bounded_strlen(tuple->elements[i], 4096);
        if (element_length > total_length - offset) {
            free(result);
            return NULL;
        }
        if (element_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, tuple->elements[i], element_length);
            offset += element_length;
        }

        if (i < tuple->count - 1) {
            if (delimiter_length > total_length - offset) {
                free(result);
                return NULL;
            }
            if (delimiter_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + offset, delimiter, delimiter_length);
                offset += delimiter_length;
            }
        }
    }

    result[offset] = '\0';
    return result;
}

int main(void) {
    const char *elements[] = {"apple", "banana", "cherry", "date"};
    Tuple tuple = {elements, sizeof(elements) / sizeof(elements[0])};
    const char *delimiter = ", ";

    char *result = concatenate_tuple(&tuple, delimiter);
    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate tuple\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    free(result);

    return EXIT_SUCCESS;
}