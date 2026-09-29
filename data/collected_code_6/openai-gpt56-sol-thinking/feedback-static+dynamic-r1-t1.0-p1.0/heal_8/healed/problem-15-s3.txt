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
    if (input == NULL || result == NULL) {
        return 0;
    }

    result->items = NULL;
    result->count = 0;

    size_t length = 0;
    size_t count = 1;

    while (input[length] != '\0') {
        if (islower((unsigned char)input[length])) {
            if (count == SIZE_MAX) {
                return 0;
            }
            ++count;
        }

        if (length == SIZE_MAX - 1) {
            return 0;
        }

        ++length;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return 0;
    }

    char **items = calloc(count, sizeof(*items));
    if (items == NULL) {
        return 0;
    }

    SplitResult temporary = {
        .items = items,
        .count = count
    };

    size_t start = 0;
    size_t part_index = 0;

    for (size_t i = 0; i < length; ++i) {
        if (!islower((unsigned char)input[i])) {
            continue;
        }

        if (!allocate_part(&temporary.items[part_index],
                           input + start,
                           i - start)) {
            free_split_result(&temporary);
            return 0;
        }

        ++part_index;
        start = i + 1;
    }

    if (!allocate_part(&temporary.items[part_index],
                       input + start,
                       length - start)) {
        free_split_result(&temporary);
        return 0;
    }

    *result = temporary;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    SplitResult result = { NULL, 0 };

    if (!split_at_lowercase(argv[1], &result)) {
        fputs("Failed to split the string.\n", stderr);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;

    for (size_t i = 0; i < result.count; ++i) {
        if (puts(result.items[i]) == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free_split_result(&result);
    return status;
}