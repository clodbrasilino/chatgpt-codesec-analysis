#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            size_t str_len = strlen(list[i]) + 1;
            tuple->elements[i] = malloc(str_len);
            if (!tuple->elements[i]) {
                tuple->length = i;
                free_string_tuple(tuple);
                return NULL;
            }
            memcpy(tuple->elements[i], list[i], str_len);
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