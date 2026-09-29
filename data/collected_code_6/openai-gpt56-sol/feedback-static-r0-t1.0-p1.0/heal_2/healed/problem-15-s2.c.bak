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

static int append_string(char ***strings, size_t *count, const char *start,
                         size_t length)
{
    if (length == SIZE_MAX || *count == SIZE_MAX ||
        *count + 1 > SIZE_MAX / sizeof **strings) {
        return -1;
    }

    char *part = malloc(length + 1);
    if (part == NULL) {
        return -1;
    }

    memcpy(part, start, length);
    part[length] = '\0';

    char **resized = realloc(*strings, (*count + 1) * sizeof *resized);
    if (resized == NULL) {
        free(part);
        return -1;
    }

    resized[*count] = part;
    *strings = resized;
    ++*count;

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

    for (const char *current = input; *current != '\0'; ++current) {
        if (islower((unsigned char)*current)) {
            if (current > segment_start &&
                append_string(parts, part_count, segment_start,
                              (size_t)(current - segment_start)) != 0) {
                free_strings(*parts, *part_count);
                *parts = NULL;
                *part_count = 0;
                return -1;
            }

            segment_start = current + 1;
        }
    }

    if (*segment_start != '\0' &&
        append_string(parts, part_count, segment_start,
                      strlen(segment_start)) != 0) {
        free_strings(*parts, *part_count);
        *parts = NULL;
        *part_count = 0;
        return -1;
    }

    return 0;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s STRING\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
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