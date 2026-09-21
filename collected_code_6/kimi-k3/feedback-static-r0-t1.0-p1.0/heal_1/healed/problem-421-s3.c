#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char **elements;
    size_t count;
} Tuple;

static int is_valid_string(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            return 1;
        }
    }
    return 0;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *concatenate_tuple(const Tuple *tuple, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple->elements == NULL || tuple->count == 0) {
        return NULL;
    }

    if (!is_valid_string(delimiter, SIZE_MAX / 2)) {
        return NULL;
    }

    size_t delimiter_length = safe_strlen(delimiter, SIZE_MAX / 2);
    size_t total_length = 0;
    size_t i;

    for (i = 0; i < tuple->count; i++) {
        if (tuple->elements[i] == NULL) {
            return NULL;
        }
        if (!is_valid_string(tuple->elements[i], SIZE_MAX / 2)) {
            return NULL;
        }
        size_t element_length = safe_strlen(tuple->elements[i], SIZE_MAX / 2);
        
        if (element_length > SIZE_MAX - total_length - 1) {
            return NULL;
        }
        total_length += element_length;
        
        if (i < tuple->count - 1) {
            if (delimiter_length > SIZE_MAX - total_length - 1) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length >= SIZE_MAX - 1) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (i = 0; i < tuple->count; i++) {
        size_t element_length = safe_strlen(tuple->elements[i], SIZE_MAX / 2);
        
        if (offset + element_length > total_length) {
            free(result);
            return NULL;
        }
        
        memcpy(result + offset, tuple->elements[i], element_length);
        offset += element_length;

        if (i < tuple->count - 1) {
            if (offset + delimiter_length > total_length) {
                free(result);
                return NULL;
            }
            memcpy(result + offset, delimiter, delimiter_length);
            offset += delimiter_length;
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