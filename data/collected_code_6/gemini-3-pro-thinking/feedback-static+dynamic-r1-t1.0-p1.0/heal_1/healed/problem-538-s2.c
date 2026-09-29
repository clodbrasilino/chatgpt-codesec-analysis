#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

typedef struct {
    char **elements;
    size_t size;
} Tuple;

static char *duplicate_string(const char *src) {
    size_t len = 0;
    char *dst;

    if (!src) {
        return NULL;
    }

    while (src[len] != '\0' && len < MAX_STRING_LEN) {
        len++;
    }

    dst = malloc(len + 1);
    if (!dst) {
        return NULL;
    }

    for (size_t k = 0; k < len; k++) {
        dst[k] = src[k];
    }
    dst[len] = '\0';

    return dst;
}

Tuple *create_tuple_from_list(const char **list, size_t size) {
    Tuple *tuple;

    if (!list && size > 0) {
        return NULL;
    }

    tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->size = size;

    if (size == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = malloc(size * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (!list[i]) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }

        tuple->elements[i] = duplicate_string(list[i]);
        if (!tuple->elements[i]) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }

    if (tuple->elements) {
        for (size_t i = 0; i < tuple->size; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    
    free(tuple);
}

int main(void) {
    const char *string_list[] = {"apple", "banana", "cherry"};
    size_t list_size = sizeof(string_list) / sizeof(string_list[0]);
    Tuple *my_tuple;

    my_tuple = create_tuple_from_list(string_list, list_size);
    if (!my_tuple) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < my_tuple->size; i++) {
        printf("%s\n", my_tuple->elements[i]);
    }

    free_tuple(my_tuple);
    
    return EXIT_SUCCESS;
}