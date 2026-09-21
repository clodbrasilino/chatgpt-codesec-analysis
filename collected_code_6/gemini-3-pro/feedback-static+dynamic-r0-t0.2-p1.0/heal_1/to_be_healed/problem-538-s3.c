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

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(list[i]);
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
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(tuple->elements[i], list[i], len + 1);
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
        printf("Failed to create tuple.\n");
    }

    return 0;
}