#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strlen(src);
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len + 1U);
    return copy;
}

Tuple *list_to_tuple(const char **list, size_t count)
{
    Tuple *tuple;
    size_t i;

    if (list == NULL && count > 0U) {
        return NULL;
    }

    tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->count = count;
    tuple->items = NULL;

    if (count > 0U) {
        tuple->items = calloc(count, sizeof(char *));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }
        for (i = 0U; i < count; i++) {
            tuple->items[i] = duplicate_string(list[i]);
            if (tuple->items[i] == NULL && list[i] != NULL) {
                size_t j;
                for (j = 0U; j < i; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }
        }
    }
    return tuple;
}

void free_tuple(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (i = 0U; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }
    if (printf("(") < 0) {
        return;
    }
    for (i = 0U; i < tuple->count; i++) {
        if (printf("\"%s\"", tuple->items[i] != NULL ? tuple->items[i] : "") < 0) {
            return;
        }
        if (i + 1U < tuple->count) {
            if (printf(", ") < 0) {
                return;
            }
        }
    }
    if (printf(")\n") < 0) {
        return;
    }
}

int main(void)
{
    const char *list[] = { "apple", "banana", "cherry" };
    size_t count = sizeof(list) / sizeof(list[0]);
    Tuple *tuple;

    tuple = list_to_tuple(list, count);
    if (tuple == NULL) {
        if (fprintf(stderr, "Failed to convert list to tuple\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    print_tuple(tuple);
    free_tuple(tuple);

    return EXIT_SUCCESS;
}