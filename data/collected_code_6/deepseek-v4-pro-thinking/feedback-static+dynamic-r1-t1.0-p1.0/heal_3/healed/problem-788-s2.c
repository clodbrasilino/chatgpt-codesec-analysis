#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char *string;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *string, const int *list, size_t list_size) {
    Tuple *tuple;

    if (!string || (list_size > 0 && !list)) {
        return NULL;
    }

    tuple = malloc(sizeof(*tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->string = NULL;
    tuple->list = NULL;
    tuple->list_size = 0;

    size_t string_len = strnlen(string, MAX_STRING_LENGTH);
    if (string_len >= MAX_STRING_LENGTH) {
        free(tuple);
        return NULL;
    }

    char *string_copy = malloc(string_len + 1);
    if (!string_copy) {
        free(tuple);
        return NULL;
    }

    strncpy(string_copy, string, string_len);
    string_copy[string_len] = '\0';
    tuple->string = string_copy;

    if (list_size > 0) {
        if (list_size > SIZE_MAX / sizeof(*list)) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }

        int *list_copy = malloc(list_size * sizeof(*list));
        if (!list_copy) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }

        for (size_t i = 0; i < list_size; ++i) {
            list_copy[i] = list[i];
        }
        tuple->list = list_copy;
        tuple->list_size = list_size;
    }

    return tuple;
}

void destroy_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }

    free(tuple->string);
    free(tuple->list);
    free(tuple);
}

int main(void) {
    int numbers[] = {1, 2, 3};
    Tuple *tuple = create_tuple("example", numbers, sizeof(numbers) / sizeof(numbers[0]));

    if (!tuple) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", tuple->string);
    printf("List: ");

    for (size_t i = 0; i < tuple->list_size; ++i) {
        printf("%d%s", tuple->list[i], (i + 1 < tuple->list_size) ? " " : "");
    }

    printf("\n");

    destroy_tuple(tuple);
    return EXIT_SUCCESS;
}