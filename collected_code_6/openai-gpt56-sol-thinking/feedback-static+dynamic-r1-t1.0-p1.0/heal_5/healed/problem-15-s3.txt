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
    if (result == NULL) {
        return;
    }

    for (size_t i = 0; i < result->count; ++i) {
        free(result->items[i]);
    }

    free(result->items);
    result->items = NULL;
    result->count = 0;
}

static int allocate_part(char **destination, const char *source, size_t length)
{
    if (destination == NULL || source == NULL || length == SIZE_MAX) {
        return 0;
    }

    char *part = malloc(length + 1);
    if (part == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        part[i] = source[i];
    }

    part[length] = '\0';
    *destination = part;
    return 1;
}

static int split_at_lowercase(const char *input, SplitResult *result)
{
    if (result == NULL) {
        return 0;
    }

    result->items = NULL;
    result->count = 0;

    if (input == NULL) {
        return 0;
    }

    size_t length = 0;

    while (input[length] != '\0') {
        if (length == SIZE_MAX - 1) {
            return 0;
        }

        ++length;
    }

    size_t count = 1;

    for (size_t i = 0; i < length; ++i) {
        if (islower((unsigned char)input[i])) {
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

    size_t start = 0;
    size_t part_index = 0;

    for (size_t i = 0; i < length; ++i) {
        if (islower((unsigned char)input[i])) {
            if (!allocate_part(&result->items[part_index],
                               input + start,
                               i - start)) {
                free_split_result(result);
                return 0;
            }

            ++part_index;
            start = i + 1;
        }
    }

    if (!allocate_part(&result->items[part_index],
                       input + start,
                       length - start)) {
        free_split_result(result);
        return 0;
    }

    return 1;
}

int main(int argc, char *const argv[])
{
    SplitResult result = { NULL, 0 };
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr,
                "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (!split_at_lowercase(argv[1], &result)) {
        fputs("Failed to split the string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.count; ++i) {
        if (puts(result.items[i]) == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    free_split_result(&result);
    return status;
}