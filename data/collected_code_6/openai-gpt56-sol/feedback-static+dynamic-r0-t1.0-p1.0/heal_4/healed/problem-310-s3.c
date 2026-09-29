#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} Tuple;

static void tuple_init(Tuple *tuple)
{
    if (tuple != NULL) {
        tuple->items = NULL;
        tuple->count = 0;
        tuple->capacity = 0;
    }
}

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple_init(tuple);
}

static int tuple_reserve(Tuple *tuple, size_t required)
{
    if (tuple == NULL) {
        return -1;
    }

    if (required <= tuple->capacity) {
        return 0;
    }

    if (required > SIZE_MAX / sizeof(*tuple->items)) {
        return -1;
    }

    size_t capacity = tuple->capacity == 0 ? 8 : tuple->capacity;

    while (capacity < required) {
        if (capacity > SIZE_MAX / 2) {
            capacity = required;
            break;
        }
        capacity *= 2;
    }

    if (capacity < required ||
        capacity > SIZE_MAX / sizeof(*tuple->items)) {
        return -1;
    }

    char **items = realloc(tuple->items, capacity * sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    tuple->items = items;
    tuple->capacity = capacity;
    return 0;
}

static int tuple_append(Tuple *tuple, const char *start, size_t length)
{
    if (tuple == NULL || start == NULL || length == SIZE_MAX) {
        return -1;
    }

    if (tuple->count == SIZE_MAX) {
        return -1;
    }

    size_t allocation_size = length + 1;
    char *item = malloc(allocation_size);
    if (item == NULL) {
        return -1;
    }

    if (length > 0) {
        memcpy(item, start, length);
    }
    item[length] = '\0';

    if (tuple_reserve(tuple, tuple->count + 1) != 0) {
        free(item);
        return -1;
    }

    tuple->items[tuple->count++] = item;
    return 0;
}

static int string_to_tuple(const char *input, char delimiter, Tuple *tuple)
{
    if (input == NULL || tuple == NULL || delimiter == '\0') {
        return -1;
    }

    tuple_init(tuple);

    const char *start = input;
    const char *cursor = input;

    for (;;) {
        if (*cursor == delimiter || *cursor == '\0') {
            size_t length = (size_t)(cursor - start);

            if (tuple_append(tuple, start, length) != 0) {
                tuple_destroy(tuple);
                return -1;
            }

            if (*cursor == '\0') {
                return 0;
            }

            start = cursor + 1;
        }

        ++cursor;
    }
}

static void tuple_print(const Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    putchar('(');

    for (size_t i = 0; i < tuple->count; ++i) {
        putchar('"');

        const unsigned char *p =
            (const unsigned char *)tuple->items[i];

        while (*p != '\0') {
            if (*p == '"' || *p == '\\') {
                putchar('\\');
            }
            putchar((int)*p);
            ++p;
        }

        putchar('"');

        if (i + 1 < tuple->count) {
            fputs(", ", stdout);
        }
    }

    puts(")");
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <comma-separated-string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Tuple tuple;
    tuple_init(&tuple);

    if (string_to_tuple(argv[1], ',', &tuple) != 0) {
        fputs("Failed to convert string to tuple\n", stderr);
        return EXIT_FAILURE;
    }

    tuple_print(&tuple);
    tuple_destroy(&tuple);

    return EXIT_SUCCESS;
}