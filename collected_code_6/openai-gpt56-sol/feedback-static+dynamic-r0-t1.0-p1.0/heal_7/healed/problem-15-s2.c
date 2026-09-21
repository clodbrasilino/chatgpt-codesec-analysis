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

static int append_string(char ***strings, size_t *count,
                         const char *start, size_t length)
{
    if (strings == NULL || count == NULL || start == NULL) {
        return -1;
    }

    if (length == SIZE_MAX || *count == SIZE_MAX) {
        return -1;
    }

    size_t new_count = *count + 1;

    if (new_count > SIZE_MAX / sizeof **strings) {
        return -1;
    }

    size_t allocation_size = length + 1;
    char *part = malloc(allocation_size);

    if (part == NULL) {
        return -1;
    }

    if (length > 0) {
        memcpy(part, start, length);
    }
    part[length] = '\0';

    char **resized = realloc(*strings, new_count * sizeof **strings);

    if (resized == NULL) {
        free(part);
        return -1;
    }

    resized[*count] = part;
    *strings = resized;
    *count = new_count;

    return 0;
}

static int split_at_lowercase(const char *input, char ***parts,
                              size_t *part_count)
{
    if (input == NULL || parts == NULL || part_count == NULL) {
        return -1;
    }

    *parts = NULL;
    *part_count = 0;

    const char *segment_start = input;
    const char *current = input;

    for (;;) {
        unsigned char character = (unsigned char)*current;

        if (character == '\0') {
            size_t length = (size_t)(current - segment_start);

            if (length > 0 &&
                append_string(parts, part_count, segment_start, length) != 0) {
                free_strings(*parts, *part_count);
                *parts = NULL;
                *part_count = 0;
                return -1;
            }

            return 0;
        }

        if (islower(character)) {
            size_t length = (size_t)(current - segment_start);

            if (length > 0 &&
                append_string(parts, part_count, segment_start, length) != 0) {
                free_strings(*parts, *part_count);
                *parts = NULL;
                *part_count = 0;
                return -1;
            }

            segment_start = current + 1;
        }

        ++current;
    }
}

int main(int argc, char *const argv[])
{
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s STRING\n", program_name);
        return EXIT_FAILURE;
    }

    char **parts = NULL;
    size_t part_count = 0;

    if (split_at_lowercase(argv[1], &parts, &part_count) != 0) {
        fputs("Failed to split string\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < part_count; ++i) {
        if (puts(parts[i]) == EOF) {
            free_strings(parts, part_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(parts, part_count);
    return EXIT_SUCCESS;
}