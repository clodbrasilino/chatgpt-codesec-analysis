#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_parts(char **parts, size_t count)
{
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(parts[i]);
    }

    free(parts);
}

static char **split_at_uppercase(const char *input, size_t input_length,
                                 size_t *count)
{
    char **parts;
    size_t part_count = 1;
    size_t part_index = 0;
    size_t start = 0;
    size_t i;

    if (input == NULL || count == NULL || input_length == 0) {
        return NULL;
    }

    *count = 0;

    for (i = 1; i < input_length; ++i) {
        if (isupper((unsigned char)input[i])) {
            if (part_count == SIZE_MAX) {
                return NULL;
            }
            ++part_count;
        }
    }

    if (part_count > SIZE_MAX / sizeof(*parts)) {
        return NULL;
    }

    parts = calloc(part_count, sizeof(*parts));
    if (parts == NULL) {
        return NULL;
    }

    for (i = 1; i <= input_length; ++i) {
        if (i == input_length || isupper((unsigned char)input[i])) {
            size_t part_length = i - start;
            size_t allocation_size;

            if (part_length == SIZE_MAX) {
                free_parts(parts, part_index);
                return NULL;
            }

            allocation_size = part_length + 1;
            parts[part_index] = malloc(allocation_size);
            if (parts[part_index] == NULL) {
                free_parts(parts, part_index);
                return NULL;
            }

            if (part_length > 0) {
                memcpy(parts[part_index], input + start, part_length);
            }
            parts[part_index][part_length] = '\0';

            ++part_index;
            start = i;
        }
    }

    *count = part_index;
    return parts;
}

int main(int argc, char *argv[])
{
    const char *input;
    char **parts;
    size_t input_length;
    size_t count;
    size_t i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_length = strlen(input);

    if (input_length == 0) {
        return EXIT_SUCCESS;
    }

    parts = split_at_uppercase(input, input_length, &count);
    if (parts == NULL) {
        fputs("Failed to split string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
            free_parts(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_parts(parts, count);
    return EXIT_SUCCESS;
}