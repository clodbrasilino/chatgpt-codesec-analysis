#include <ctype.h>
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);

    for (index = 0; index < length; ++index) {
        if (islower((unsigned char)input[index])) {
            if (count == SIZE_MAX) {
                return 0;
            }
            ++count;
        }
    }

    result->items = calloc(count, sizeof(*result->items));
    if (result->items == NULL) {
        return 0;
    }
    result->count = count;

    for (index = 0; index <= length; ++index) {
        if (index == length || islower((unsigned char)input[index])) {
            size_t part_length = index - start;

            if (part_length == SIZE_MAX) {
                free_split_result(result);
                return 0;
            }

            result->items[part_index] = malloc(part_length + 1);
            if (result->items[part_index] == NULL) {
                free_split_result(result);
                return 0;
            }

            if (part_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result->items[part_index], input + start, part_length);
            }
            result->items[part_index][part_length] = '\0';
            ++part_index;
            start = index + 1;
        }
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    SplitResult result;
    size_t i;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
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