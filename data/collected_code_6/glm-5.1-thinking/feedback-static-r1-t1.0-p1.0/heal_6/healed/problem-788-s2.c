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
    size_t actual_str_len;
    size_t dest_str_size;
    const char *null_pos;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    null_pos = memchr(str, '\0', str_len);
    actual_str_len = null_pos ? (size_t)(null_pos - str) : str_len;

    if (actual_str_len == SIZE_MAX) {
        free(tuple);
        return NULL;
    }

    dest_str_size = actual_str_len + 1;
    tuple->string = malloc(dest_str_size);
    if (tuple->string == NULL) {
        free(tuple);
        return NULL;
    }

    memcpy(tuple->string, str, actual_str_len);
    tuple->string[actual_str_len] = '\0';

    if (list_size > 0) {
        if (list_size > SIZE_MAX / sizeof(int)) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }
        size_t dest_list_size = list_size * sizeof(int);
        tuple->list = malloc(dest_list_size);
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
    const char str[] = "example";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    Tuple *t = create_tuple(str, sizeof(str) - 1, list, list_size);
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