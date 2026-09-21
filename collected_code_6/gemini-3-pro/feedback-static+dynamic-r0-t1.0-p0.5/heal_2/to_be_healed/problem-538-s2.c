#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t size;
} StringTuple;

StringTuple* convert_list_to_tuple(char **list, size_t size) {
    if (list == NULL || size == 0) {
        return NULL;
    }

    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = (char **)malloc(size * sizeof(char *));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->size = size;

    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }

        size_t len = 0;
        while (list[i][len] != '\0') {
            len++;
        }

        tuple->elements[i] = (char *)malloc((len + 1) * sizeof(char));
        if (tuple->elements[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->elements[i], list[i], len + 1);
    }

    return tuple;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        if (tuple->elements != NULL) {
            for (size_t i = 0; i < tuple->size; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(void) {
    char *string_list[] = {"apple", "banana", "cherry"};
    size_t list_size = sizeof(string_list) / sizeof(string_list[0]);

    StringTuple *tuple = convert_list_to_tuple(string_list, list_size);

    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            printf("%s\n", tuple->elements[i]);
        }
        free_tuple(tuple);
    } else {
        fprintf(stderr, "Failed to convert list to tuple.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}