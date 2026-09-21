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

static char **split_at_uppercase(const char *input, size_t *part_count)
{
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
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
            size_t part_length = i - start;
            char *part;

            if (part_length > SIZE_MAX - 1) {
                goto failure;
            }

            part = malloc(part_length + 1);
            if (part == NULL) {
                goto failure;
            }

            if (part_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(part, input + start, part_length);
            }
            part[part_length] = '\0';

            if (count == capacity) {
                size_t new_capacity;
                char **resized;

                if (capacity == 0) {
                    new_capacity = 4;
                } else {
                    if (capacity > SIZE_MAX / 2) {
                        free(part);
                        goto failure;
                    }
                    new_capacity = capacity * 2;
                }

                if (new_capacity > SIZE_MAX / sizeof(*parts)) {
                    free(part);
                    goto failure;
                }

                resized = realloc(parts, new_capacity * sizeof(*parts));
                if (resized == NULL) {
                    free(part);
                    goto failure;
                }

                parts = resized;
                capacity = new_capacity;
            }

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
    size_t count = 0;
    size_t i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        return EXIT_SUCCESS;
    }

    parts = split_at_uppercase(argv[1], &count);
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