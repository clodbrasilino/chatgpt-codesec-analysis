#include <ctype.h>
#include <stdint.h>
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

static int split_at_uppercase(const char *input, size_t input_length,
                              char ***parts, size_t *count)
{
    char **result = NULL;
    size_t part_count = 1;
    size_t part_index = 0;
    size_t start = 0;

    if (input == NULL || parts == NULL || count == NULL) {
        return -1;
    }

    *parts = NULL;
    *count = 0;

    if (input_length == 0) {
        return 0;
    }

    for (size_t i = 1; i < input_length; ++i) {
        if (isupper((unsigned char)input[i])) {
            if (part_count == SIZE_MAX) {
                return -1;
            }
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

    for (size_t i = 1; i <= input_length; ++i) {
        if (i == input_length || isupper((unsigned char)input[i])) {
            size_t part_length = i - start;
            size_t allocation_size;

            if (part_length > SIZE_MAX - 1) {
                free_strings(result, part_index);
                return -1;
            }

            /* Possible weaknesses found:
             *  allocation_size is assigned 'part_length+1' here.
             */
            allocation_size = part_length + 1;
            result[part_index] = malloc(allocation_size);
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (result[part_index] == NULL) {
                free_strings(result, part_index);
                return -1;
            }

            /* Possible weaknesses found:
             *  Condition 'part_length>=allocation_size' is always false [knownConditionTrueFalse]
             *  Condition 'part_length>=allocation_size' is always false
             */
            if (part_length >= allocation_size) {
                free_strings(result, part_index + 1);
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
    *count = part_index;
    return 0;
}

int main(int argc, char *argv[])
{
    char **parts = NULL;
    size_t count = 0;
    size_t input_length;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(argv[1]);

    if (split_at_uppercase(argv[1], input_length, &parts, &count) != 0) {
        fputs("Failed to split string\n", stderr);
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