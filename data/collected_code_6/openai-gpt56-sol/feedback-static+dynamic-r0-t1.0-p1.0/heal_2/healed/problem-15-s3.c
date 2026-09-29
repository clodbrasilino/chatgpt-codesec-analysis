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
        *count + 1 > SIZE_MAX / sizeof **strings) {
        return 0;
    }

    char *part = malloc(length + 1);
    if (part == NULL) {
        return 0;
    }

    if (length != 0) {
        memmove(part, start, length);
    }
    part[length] = '\0';

    size_t new_count = *count + 1;
    char **resized = realloc(*strings, new_count * sizeof *resized);
    if (resized == NULL) {
        free(part);
        return 0;
    }

    resized[*count] = part;
    *strings = resized;
    *count = new_count;

    return 1;
}

static int split_at_lowercase(const char *input, char ***result,
                              size_t *count)
{
    if (input == NULL || result == NULL || count == NULL) {
        return 0;
    }

    *result = NULL;
    *count = 0;

    char **parts = NULL;
    size_t part_count = 0;
    const char *start = input;

    for (const char *current = input;; ++current) {
        if (*current == '\0') {
            if (current != start &&
                !append_string(&parts, &part_count, start,
                               (size_t)(current - start))) {
                free_strings(parts, part_count);
                return 0;
            }
            break;
        }

        if (islower((unsigned char)*current)) {
            if (current != start &&
                !append_string(&parts, &part_count, start,
                               (size_t)(current - start))) {
                free_strings(parts, part_count);
                return 0;
            }

            start = current + 1;
        }
    }

    *result = parts;
    *count = part_count;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    char **parts = NULL;
    size_t count = 0;

    if (!split_at_lowercase(input, &parts, &count)) {
        fprintf(stderr, "Unable to split string\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        puts(parts[i]);
    }

    free_strings(parts, count);
    return EXIT_SUCCESS;
}