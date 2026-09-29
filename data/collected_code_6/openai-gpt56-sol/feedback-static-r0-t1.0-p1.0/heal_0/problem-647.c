#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **split_at_uppercase(const char *input, size_t *count)
{
    char **parts = NULL;
    size_t length;
    size_t part_count = 0;
    size_t start = 0;
    size_t index;
    size_t part_index;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    length = strlen(input);

    if (length == 0) {
        return NULL;
    }

    part_count = 1;
    for (index = 1; index < length; ++index) {
        if (isupper((unsigned char)input[index])) {
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

    part_index = 0;
    for (index = 1; index <= length; ++index) {
        if (index == length || isupper((unsigned char)input[index])) {
            size_t part_length = index - start;

            if (part_length == SIZE_MAX) {
                goto failure;
            }

            parts[part_index] = malloc(part_length + 1);
            if (parts[part_index] == NULL) {
                goto failure;
            }

            memcpy(parts[part_index], input + start, part_length);
            parts[part_index][part_length] = '\0';
            ++part_index;
            start = index;
        }
    }

    *count = part_count;
    return parts;

failure:
    while (part_index > 0) {
        free(parts[--part_index]);
    }
    free(parts);
    return NULL;
}

static void free_parts(char **parts, size_t count)
{
    size_t index;

    if (parts == NULL) {
        return;
    }

    for (index = 0; index < count; ++index) {
        free(parts[index]);
    }

    free(parts);
}

int main(int argc, char *argv[])
{
    char **parts;
    size_t count;
    size_t index;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parts = split_at_uppercase(argv[1], &count);
    if (parts == NULL) {
        if (argv[1][0] == '\0') {
            return EXIT_SUCCESS;
        }

        fputs("Failed to split string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        if (puts(parts[index]) == EOF) {
            free_parts(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_parts(parts, count);
    return EXIT_SUCCESS;
}