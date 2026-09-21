#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char **elements;
    size_t length;
} StringTuple;

void free_string_tuple(StringTuple *tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->elements) {
        for (size_t i = 0; i < tuple->length; ++i) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    free(tuple);
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

StringTuple* create_tuple_from_list(const char *const *list, size_t length) {
    if (!list && length > 0) {
        return NULL;
    }

    StringTuple *tuple = malloc(sizeof(StringTuple));
    if (!tuple) {
        return NULL;
    }

    tuple->length = length;
    if (length == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = malloc(length * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!list[i]) {
            tuple->elements[i] = NULL;
        } else {
            size_t str_len = safe_strlen(list[i], MAX_STRING_LENGTH);
            tuple->elements[i] = malloc(str_len + 1);
            if (!tuple->elements[i]) {
                tuple->length = i;
                free_string_tuple(tuple);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tuple->elements[i], list[i], str_len);
            tuple->elements[i][str_len] = '\0';
        }
    }

    return tuple;
}

int main(void) {
    const char *const list[] = {"apple", "banana", "cherry"};
    size_t length = sizeof(list) / sizeof(list[0]);

    StringTuple *tuple = create_tuple_from_list(list, length);
    if (!tuple) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->length; ++i) {
        if (tuple->elements[i]) {
            printf("%s\n", tuple->elements[i]);
        }
    }

    free_string_tuple(tuple);
    return EXIT_SUCCESS;
}