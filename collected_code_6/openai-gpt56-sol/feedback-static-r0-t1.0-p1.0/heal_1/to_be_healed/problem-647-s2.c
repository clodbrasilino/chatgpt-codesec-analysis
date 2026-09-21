#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_strings(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int split_at_uppercase(const char *input, char ***parts, size_t *count)
{
    size_t input_length;
    size_t part_count;
    size_t start;
    size_t part_index;
    char **result;

    if (input == NULL || parts == NULL || count == NULL) {
        return -1;
    }

    *parts = NULL;
    *count = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);
    if (input_length == 0) {
        return 0;
    }

    part_count = 1;
    for (size_t i = 1; i < input_length; ++i) {
        if (isupper((unsigned char)input[i]) != 0) {
            ++part_count;
        }
    }

    if (part_count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(part_count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    start = 0;
    part_index = 0;

    for (size_t i = 1; i <= input_length; ++i) {
        if (i == input_length || isupper((unsigned char)input[i]) != 0) {
            size_t part_length = i - start;

            if (part_length == SIZE_MAX) {
                free_strings(result, part_index);
                return -1;
            }

            result[part_index] = malloc(part_length + 1);
            if (result[part_index] == NULL) {
                free_strings(result, part_index);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[part_index], input + start, part_length);
            result[part_index][part_length] = '\0';

            ++part_index;
            start = i;
        }
    }

    *parts = result;
    *count = part_count;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char **parts;
    size_t count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (split_at_uppercase(argv[1], &parts, &count) != 0) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
            free_strings(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_strings(parts, count);
    return EXIT_SUCCESS;
}