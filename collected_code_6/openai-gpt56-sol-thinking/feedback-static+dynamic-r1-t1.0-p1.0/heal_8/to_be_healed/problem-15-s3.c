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

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(part, source, length);
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

    if (count > SIZE_MAX / sizeof(*result->items)) {
        return 0;
    }

    SplitResult temporary = {
        .items = calloc(count, sizeof(*temporary.items)),
        .count = count
    };

    if (temporary.items == NULL) {
        return 0;
    }

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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

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

    free_split_result(&result);
    return status;
}