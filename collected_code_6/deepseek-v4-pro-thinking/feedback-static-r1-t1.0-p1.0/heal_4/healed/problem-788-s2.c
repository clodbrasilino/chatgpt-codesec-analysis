#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *string, size_t string_len, const int *list, size_t list_size) {
    Tuple *tuple;
    char *string_copy;
    int *list_copy;

    if (string_len > 0 && !string) {
        return NULL;
    }
    if (list_size > 0 && !list) {
        return NULL;
    }
    if (string_len == SIZE_MAX) {
        return NULL;
    }

    tuple = malloc(sizeof(*tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->string = NULL;
    tuple->list = NULL;
    tuple->list_size = 0;

    if (string_len > 0) {
        string_copy = strndup(string, string_len);
        if (!string_copy) {
            free(tuple);
            return NULL;
        }
        tuple->string = string_copy;
    } else {
        string_copy = malloc(1);
        if (!string_copy) {
            free(tuple);
            return NULL;
        }
        string_copy[0] = '\0';
        tuple->string = string_copy;
    }

    if (list_size > 0) {
        if (list_size > SIZE_MAX / sizeof(*list_copy)) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }
        list_copy = malloc(list_size * sizeof(*list_copy));
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
    const char *text = "example";
    Tuple *tuple = create_tuple(text, strlen(text), numbers, sizeof(numbers) / sizeof(numbers[0]));

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