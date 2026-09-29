#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

enum {
    TUPLE_OK = 0,
    TUPLE_EINVAL = -1,
    TUPLE_ENOMEM = -2
};

static char *string_duplicate(const char *src) {
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strlen(src);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len + 1);
    return copy;
}

int string_list_to_tuple(char **list, Tuple *tuple) {
    size_t count;
    size_t i;
    char **items;

    if (list == NULL || tuple == NULL) {
        return TUPLE_EINVAL;
    }
    count = 0;
    while (list[count] != NULL) {
        count++;
    }
    if (count == 0) {
        tuple->items = NULL;
        tuple->count = 0;
        return TUPLE_OK;
    }
    items = malloc(count * sizeof(*items));
    if (items == NULL) {
        return TUPLE_ENOMEM;
    }
    for (i = 0; i < count; i++) {
        items[i] = string_duplicate(list[i]);
        if (items[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(items[j]);
            }
            free(items);
            return TUPLE_ENOMEM;
        }
    }
    tuple->items = items;
    tuple->count = count;
    return TUPLE_OK;
}

void tuple_free(Tuple *tuple) {
    size_t i;

    if (tuple == NULL) {
        return;
    }
    for (i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

int main(void) {
    char *list[] = {"apple", "banana", "cherry", NULL};
    Tuple tuple = {0};
    int result;

    result = string_list_to_tuple(list, &tuple);
    if (result != TUPLE_OK) {
        fprintf(stderr, "Error: unable to convert list to tuple\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < tuple.count; i++) {
        printf("%s\n", tuple.items[i]);
    }
    tuple_free(&tuple);
    return EXIT_SUCCESS;
}