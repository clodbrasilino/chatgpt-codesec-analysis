#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

static int tuple_append(Tuple *tuple, const char *start, size_t length)
{
    if (tuple == NULL || start == NULL || length == SIZE_MAX) {
        return -1;
    }

    if (tuple->count >= SIZE_MAX / sizeof(*tuple->items)) {
        return -1;
    }

    char *item = malloc(length + 1);
    if (item == NULL) {
        return -1;
    }

    memcpy(item, start, length);
    item[length] = '\0';

    size_t new_count = tuple->count + 1;
    char **new_items = realloc(tuple->items,
                               new_count * sizeof(*new_items));
    if (new_items == NULL) {
        free(item);
        return -1;
    }

    tuple->items = new_items;
    tuple->items[tuple->count] = item;
    tuple->count = new_count;

    return 0;
}

static int string_to_tuple(const char *input, Tuple *tuple)
{
    if (input == NULL || tuple == NULL) {
        return -1;
    }

    tuple->items = NULL;
    tuple->count = 0;

    for (const char *cursor = input; *cursor != '\0'; ++cursor) {
        if (tuple_append(tuple, cursor, 1) != 0) {
            tuple_destroy(tuple);
            return -1;
        }
    }

    return 0;
}

static void tuple_print(const Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    putchar('[');

    for (size_t i = 0; i < tuple->count; ++i) {
        printf("'%s'%s",
               tuple->items[i],
               i + 1 < tuple->count ? ", " : "");
    }

    puts("]");
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Tuple tuple = {NULL, 0};

    if (string_to_tuple(argv[1], &tuple) != 0) {
        fputs("Failed to convert string to tuple\n", stderr);
        return EXIT_FAILURE;
    }

    tuple_print(&tuple);
    tuple_destroy(&tuple);

    return EXIT_SUCCESS;
}