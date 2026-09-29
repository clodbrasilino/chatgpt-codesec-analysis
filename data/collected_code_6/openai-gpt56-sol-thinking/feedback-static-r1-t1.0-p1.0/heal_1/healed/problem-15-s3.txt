#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **items;
    size_t count;
} SplitResult;

static void free_split_result(SplitResult *result)
{
    size_t i;

    if (result == NULL) {
        return;
    }

    if (result->items != NULL) {
        for (i = 0; i < result->count; ++i) {
            free(result->items[i]);
        }

        free(result->items);
    }

    result->items = NULL;
    result->count = 0;
}

static int get_string_length(const char *input, size_t *length)
{
    size_t n = 0;

    if (input == NULL || length == NULL) {
        return 0;
    }

    while (input[n] != '\0') {
        if (n == SIZE_MAX - 1) {
            return 0;
        }
        ++n;
    }

    *length = n;
    return 1;
}

static int split_at_lowercase(const char *input, size_t length,
                              SplitResult *result)
{
    size_t count = 1;
    size_t start = 0;
    size_t index;
    size_t part_index = 0;

    if (result == NULL) {
        return 0;
    }

    result->items = NULL;
    result->count = 0;

    if (input == NULL) {
        return 0;
    }

    for (index = 0; index < length; ++index) {
        if (islower((unsigned char)input[index])) {
            if (count == SIZE_MAX) {
                return 0;
            }
            ++count;
        }
    }

    if (count > SIZE_MAX / sizeof(*result->items)) {
        return 0;
    }

    result->items = calloc(count, sizeof(*result->items));
    if (result->items == NULL) {
        return 0;
    }

    result->count = count;
    index = 0;

    for (;;) {
        if (index == length || islower((unsigned char)input[index])) {
            size_t part_length = index - start;
            size_t i;

            if (part_index >= count || part_length == SIZE_MAX) {
                free_split_result(result);
                return 0;
            }

            result->items[part_index] = malloc(part_length + 1);
            if (result->items[part_index] == NULL) {
                free_split_result(result);
                return 0;
            }

            for (i = 0; i < part_length; ++i) {
                result->items[part_index][i] = input[start + i];
            }

            result->items[part_index][part_length] = '\0';
            ++part_index;

            if (index == length) {
                break;
            }

            start = index + 1;
        }

        ++index;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    SplitResult result = { NULL, 0 };
    size_t input_length;
    size_t i;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (!get_string_length(argv[1], &input_length)) {
        fputs("Invalid input string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!split_at_lowercase(argv[1], input_length, &result)) {
        fputs("Failed to split the string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result.count; ++i) {
        if (puts(result.items[i]) == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    free_split_result(&result);
    return status;
}