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
    if (strings == NULL || count == NULL || start == NULL ||
        length == SIZE_MAX || *count == SIZE_MAX ||
        *count + 1 > SIZE_MAX / sizeof(char *)) {
        return 0;
    }

    char *part = malloc(length + 1);
    if (part == NULL) {
        return 0;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(part, start, length);
    }
    part[length] = '\0';

    char **resized = realloc(*strings, (*count + 1) * sizeof(char *));
    if (resized == NULL) {
        free(part);
        return 0;
    }

    resized[*count] = part;
    *strings = resized;
    ++*count;

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
        if (islower((unsigned char)*current)) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    size_t count = 0;
    char **parts = split_at_lowercase(argv[1], &count);

    if (parts == NULL && count == 0) {
        int should_have_parts = 0;
        const char *start = argv[1];

        for (const char *p = argv[1]; *p != '\0'; ++p) {
            if (islower((unsigned char)*p)) {
                if (p != start) {
                    should_have_parts = 1;
                    break;
                }
                start = p + 1;
            }
        }

        if (*start != '\0') {
            should_have_parts = 1;
        }

        if (should_have_parts) {
            fputs("Unable to split string\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        puts(parts[i]);
    }

    free_strings(parts, count);
    return EXIT_SUCCESS;
}