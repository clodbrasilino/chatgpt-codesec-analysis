#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096

typedef struct {
    char *items;
    size_t count;
} Tuple;

static size_t bounded_length(const char *input, size_t max_length)
{
    size_t i = 0;

    while (i < max_length && input[i] != '\0') {
        i++;
    }

    return i;
}

Tuple *string_to_tuple(const char *input)
{
    Tuple *tuple = NULL;
    size_t length = 0;
    char *items = NULL;

    if (input == NULL) {
        return NULL;
    }

    length = bounded_length(input, MAX_INPUT_LENGTH);
    if (length == 0 || length >= MAX_INPUT_LENGTH) {
        return NULL;
    }

    items = malloc(length + 1);
    if (items == NULL) {
        return NULL;
    }

    memcpy(items, input, length);
    items[length] = '\0';

    tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        free(items);
        return NULL;
    }

    tuple->items = items;
    tuple->count = length;
    return tuple;
}

void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        tuple->items = NULL;
        tuple->count = 0;
        free(tuple);
    }
}

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL || tuple->items == NULL || tuple->count == 0) {
        return;
    }

    printf("[");
    for (i = 0; i < tuple->count; i++) {
        printf("'%c'", tuple->items[i]);
        if (i + 1 < tuple->count) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);
}

int main(void)
{
    const char *inputs[] = { "python3.0", "item1", "15.10" };
    size_t i;
    size_t n = sizeof(inputs) / sizeof(inputs[0]);

    for (i = 0; i < n; i++) {
        Tuple *tuple = string_to_tuple(inputs[i]);

        if (tuple == NULL) {
            fprintf(stderr, "Failed to convert string to tuple: \"%s\"\n",
                    inputs[i]);
            return EXIT_FAILURE;
        }

        print_tuple(tuple);

        free_tuple(tuple);
    }

    return EXIT_SUCCESS;
}