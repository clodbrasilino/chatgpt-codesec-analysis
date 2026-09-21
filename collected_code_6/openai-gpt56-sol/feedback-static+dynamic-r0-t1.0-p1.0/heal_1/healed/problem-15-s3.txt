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
        return 0;
    }

    if (length == SIZE_MAX ||
        *count == SIZE_MAX ||
        *count + 1 > SIZE_MAX / sizeof(**strings)) {
        return 0;
    }

    char *part = malloc(length + 1);
    if (part == NULL) {
        return 0;
    }

    if (length > 0) {
        memcpy(part, start, length);
    }
    part[length] = '\0';

    size_t new_count = *count + 1;
    char **resized = realloc(*strings, new_count * sizeof(*resized));
    if (resized == NULL) {
        free(part);
        return 0;
    }

    resized[*count] = part;
    *strings = resized;
    *count = new_count;

    return 1;
}

static char **split_at_lowercase(const char *input, size_t *count)
{
    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    char **parts = NULL;
    size_t part_count = 0;
    const char *start = input;
    const char *current = input;

    while (*current != '\0') {
        if (islower((unsigned char)*current) != 0) {
            if (current != start &&
                !append_string(&parts, &part_count, start,
                               (size_t)(current - start))) {
                free_strings(parts, part_count);
                return NULL;
            }

            start = current + 1;
        }

        ++current;
    }

    if (current != start &&
        !append_string(&parts, &part_count, start,
                       (size_t)(current - start))) {
        free_strings(parts, part_count);
        return NULL;
    }

    *count = part_count;
    return parts;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t count = 0;
    char **parts = split_at_lowercase(argv[1], &count);

    if (parts == NULL && count == 0) {
        int has_output = 0;

        for (const char *p = argv[1]; *p != '\0'; ++p) {
            if (islower((unsigned char)*p) == 0) {
                has_output = 1;
                break;
            }
        }

        if (has_output) {
            fprintf(stderr, "Unable to split string\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        puts(parts[i]);
    }

    free_strings(parts, count);
    return EXIT_SUCCESS;
}