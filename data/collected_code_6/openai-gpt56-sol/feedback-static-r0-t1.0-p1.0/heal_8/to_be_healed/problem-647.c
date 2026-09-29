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
            char *part;

            if (part_length > SIZE_MAX - 1) {
                free_parts(parts, part_index);
                return NULL;
            }

            part = malloc(part_length + 1);
            if (part == NULL) {
                free_parts(parts, part_index);
                return NULL;
            }

            if (part_length != 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(part, input + start, part_length);
            }
            part[part_length] = '\0';

            parts[part_index++] = part;
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

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            name = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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