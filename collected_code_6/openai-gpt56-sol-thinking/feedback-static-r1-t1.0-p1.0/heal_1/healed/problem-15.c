#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_lowercase(unsigned char character)
{
    return character >= (unsigned char)'a' &&
           character <= (unsigned char)'z';
}

static void free_split(char **parts, size_t count)
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

static char *copy_part(const char *source, size_t length)
{
    char *copy;
    size_t i;

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    return copy;
}

static char **split_at_lowercase(const char *string, size_t *part_count)
{
    char **parts;
    size_t count = 0;
    size_t index = 0;
    size_t part_index = 0;
    size_t allocation_count;
    int inside_part = 0;

    if (string == NULL || part_count == NULL) {
        return NULL;
    }

    *part_count = 0;

    while (string[index] != '\0') {
        if (is_lowercase((unsigned char)string[index])) {
            inside_part = 0;
        } else if (!inside_part) {
            if (count == SIZE_MAX) {
                return NULL;
            }

            ++count;
            inside_part = 1;
        }

        ++index;
    }

    allocation_count = count == 0 ? 1 : count;

    if (allocation_count > SIZE_MAX / sizeof(*parts)) {
        return NULL;
    }

    parts = calloc(allocation_count, sizeof(*parts));
    if (parts == NULL) {
        return NULL;
    }

    index = 0;

    while (string[index] != '\0') {
        size_t start;
        size_t length;

        while (string[index] != '\0' &&
               is_lowercase((unsigned char)string[index])) {
            ++index;
        }

        if (string[index] == '\0') {
            break;
        }

        start = index;

        while (string[index] != '\0' &&
               !is_lowercase((unsigned char)string[index])) {
            ++index;
        }

        length = index - start;

        if (part_index >= count) {
            free_split(parts, part_index);
            return NULL;
        }

        parts[part_index] = copy_part(string + start, length);
        if (parts[part_index] == NULL) {
            free_split(parts, part_index);
            return NULL;
        }

        ++part_index;
    }

    *part_count = part_index;
    return parts;
}

int main(int argc, char **const argv)
{
    char **parts;
    size_t count;
    size_t i;
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    parts = split_at_lowercase(argv[1], &count);
    if (parts == NULL) {
        fputs("Unable to split the string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
            free_split(parts, count);
            fputs("Output error.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    free_split(parts, count);
    return EXIT_SUCCESS;
}