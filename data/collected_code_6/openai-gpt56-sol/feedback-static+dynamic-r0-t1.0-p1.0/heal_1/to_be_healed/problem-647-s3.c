#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **split_at_uppercase(const char *input, size_t *part_count)
{
    char **parts = NULL;
    size_t count = 0;
    size_t start = 0;
    size_t length;
    size_t i;

    if (input == NULL || part_count == NULL) {
        return NULL;
    }

    *part_count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);

    if (length == 0) {
        return NULL;
    }

    for (i = 1; i <= length; ++i) {
        if (i == length || isupper((unsigned char)input[i])) {
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

            part = malloc(part_length + 1);
            if (part == NULL) {
                goto failure;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(part, input + start, part_length);
            part[part_length] = '\0';
            parts[count++] = part;
            start = i;
        }
    }

    *part_count = count;
    return parts;

failure:
    for (i = 0; i < count; ++i) {
        free(parts[i]);
    }
    free(parts);
    return NULL;
}

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

int main(int argc, char *argv[])
{
    char **parts;
    size_t count;
    size_t i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parts = split_at_uppercase(argv[1], &count);
    if (parts == NULL) {
        if (argv[1][0] == '\0') {
            return EXIT_SUCCESS;
        }

        fprintf(stderr, "Unable to split the string\n");
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