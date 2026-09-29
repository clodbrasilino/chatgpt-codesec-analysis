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
                                 size_t *part_count)
{
    char **parts = NULL;
    size_t count = 0;
    size_t start = 0;
    size_t i;

    if (input == NULL || part_count == NULL) {
        return NULL;
    }

    *part_count = 0;

    if (input_length == 0) {
        return NULL;
    }

    for (i = 1; i <= input_length; ++i) {
        if (i == input_length || isupper((unsigned char)input[i])) {
            char **resized;
            char *part;
            size_t part_length = i - start;

            if (count == SIZE_MAX / sizeof(*parts)) {
                goto failure;
            }

            resized = realloc(parts, (count + 1) * sizeof(*parts));
            if (resized == NULL) {
                goto failure;
            }
            parts = resized;

            if (part_length == SIZE_MAX) {
                goto failure;
            }

            part = malloc(part_length + 1);
            if (part == NULL) {
                goto failure;
            }

            if (part_length > 0) {
                memcpy(part, input + start, part_length);
            }
            part[part_length] = '\0';

            parts[count++] = part;
            start = i;
        }
    }

    *part_count = count;
    return parts;

failure:
    free_parts(parts, count);
    return NULL;
}

int main(int argc, char *argv[])
{
    char **parts;
    size_t input_length;
    size_t count;
    size_t i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input_length = strlen(argv[1]);

    if (input_length == 0) {
        return EXIT_SUCCESS;
    }

    parts = split_at_uppercase(argv[1], input_length, &count);
    if (parts == NULL) {
        fputs("Unable to split the string\n", stderr);
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