#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    char *string;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, size_t str_len, const int *list, size_t list_size) {
    Tuple *tuple;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    if (str_len == SIZE_MAX || str_len > INT_MAX) {
        free(tuple);
        return NULL;
    }

    tuple->string = malloc(str_len + 1);
    if (tuple->string == NULL) {
        free(tuple);
        return NULL;
    }
    
    snprintf(tuple->string, str_len + 1, "%.*s", (int)str_len, str);

    if (list_size > 0) {
        if (list_size > SIZE_MAX / sizeof(int)) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }
        tuple->list = malloc(list_size * sizeof(int));
        if (tuple->list == NULL) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < list_size; i++) {
            tuple->list[i] = list[i];
        }
    } else {
        tuple->list = NULL;
    }

    tuple->list_size = list_size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->string);
        free(tuple->list);
        free(tuple);
    }
}

int main(void) {
    const char *str = "example";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    Tuple *t = create_tuple(str, strlen(str), list, list_size);
    if (t == NULL) {
        return EXIT_FAILURE;
    }

    printf("String: %s\n", t->string);
    printf("List: ");
    for (size_t i = 0; i < t->list_size; i++) {
        printf("%d ", t->list[i]);
    }
    printf("\n");

    free_tuple(t);

    return EXIT_SUCCESS;
}