#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    for (i = 0; i < result->count; ++i) {
        free(result->items[i]);
    }

    free(result->items);
    result->items = NULL;
    result->count = 0;
}

static int set_part(SplitResult *result, size_t index,
                    const char *start, size_t length)
{
    char *part;

    if (length == SIZE_MAX) {
        return 0;
    }

    part = malloc(length + 1);
    if (part == NULL) {
        return 0;
    }

    if (length > 0) {
        memcpy(part, start, length);
    }

    part[length] = '\0';
    result->items[index] = part;
    return 1;
}

static int split_at_lowercase(const char *input, SplitResult *result)
{
    size_t length;
    size_t count = 1;
    size_t start = 0;
    size_t index;
    size_t part_index = 0;

    if (input == NULL || result == NULL) {
        return 0;
    }

    result->items = NULL;
    result->count = 0;
    length = strlen(input);

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

    for (index = 0; index < length; ++index) {
        if (islower((unsigned char)input[index])) {
            if (!set_part(result, part_index, input + start, index - start)) {
                free_split_result(result);
                return 0;
            }

            ++part_index;
            start = index + 1;
        }
    }

    if (!set_part(result, part_index, input + start, length - start)) {
        free_split_result(result);
        return 0;
    }

    return 1;
}

int main(int argc, char *const argv[])
{
    SplitResult result;
    const char *program_name;
    size_t i;
    int status = EXIT_SUCCESS;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (!split_at_lowercase(argv[1], &result)) {
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