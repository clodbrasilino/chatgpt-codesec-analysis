#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

static void free_tuple(StringTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

static char *duplicate_character(char character)
{
    char *copy = malloc(2);

    if (copy == NULL) {
        return NULL;
    }

    copy[0] = character;
    copy[1] = '\0';

    return copy;
}

static int string_to_tuple(const char *input, size_t length, StringTuple *tuple)
{
    char **items;
    size_t i;

    if (input == NULL || tuple == NULL) {
        return -1;
    }

    tuple->items = NULL;
    tuple->count = 0;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*items)) {
        return -1;
    }

    items = calloc(length, sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        items[i] = duplicate_character(input[i]);
        if (items[i] == NULL) {
            tuple->items = items;
            tuple->count = i;
            free_tuple(tuple);
            return -1;
        }
    }

    tuple->items = items;
    tuple->count = length;

    return 0;
}

static void print_tuple(const StringTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    putchar('(');

    for (i = 0; i < tuple->count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }

        printf("\"%s\"", tuple->items[i]);
    }

    if (tuple->count == 1) {
        putchar(',');
    }

    puts(")");
}

int main(int argc, char *argv[])
{
    StringTuple tuple = {NULL, 0};
    const char *input;
    size_t input_length;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    if (input == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (string_to_tuple(input, input_length, &tuple) != 0) {
        fputs("Failed to convert string to tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    print_tuple(&tuple);
    free_tuple(&tuple);

    return EXIT_SUCCESS;
}