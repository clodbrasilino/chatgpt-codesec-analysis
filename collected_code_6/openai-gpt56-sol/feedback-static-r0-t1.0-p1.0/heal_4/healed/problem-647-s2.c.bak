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

static int split_at_uppercase(const char *input, char ***parts, size_t *count)
{
    size_t input_length;
    size_t part_count = 1;
    size_t start = 0;
    size_t part_index = 0;
    char **result;

    if (input == NULL || parts == NULL || count == NULL) {
        return -1;
    }

    *parts = NULL;
    *count = 0;

    input_length = strlen(input);
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
            const size_t part_length = i - start;

            if (part_length == SIZE_MAX) {
                free_strings(result, part_index);
                return -1;
            }

            result[part_index] = malloc(part_length + 1);
            if (result[part_index] == NULL) {
                free_strings(result, part_index);
                return -1;
            }

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

int main(int argc, char *const argv[])
{
    char **parts = NULL;
    size_t count = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (split_at_uppercase(argv[1], &parts, &count) != 0) {
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