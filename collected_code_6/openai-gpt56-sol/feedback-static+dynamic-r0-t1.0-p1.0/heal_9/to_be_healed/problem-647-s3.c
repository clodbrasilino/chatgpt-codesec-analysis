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
                                 size_t *part_count)
{
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t start = 0;
    size_t i;

    if (input == NULL || part_count == NULL || input_length == 0) {
        return NULL;
    }

    *part_count = 0;

    for (i = 1; i < input_length; ++i) {
        if (isupper((unsigned char)input[i])) {
            size_t part_length = i - start;
            char *part;

            if (count == capacity) {
                size_t new_capacity;
                char **resized;

                if (capacity == 0) {
                    new_capacity = 4;
                } else {
                    if (capacity > SIZE_MAX / 2) {
                        goto failure;
                    }
                    new_capacity = capacity * 2;
                }

                if (new_capacity > SIZE_MAX / sizeof(*parts)) {
                    goto failure;
                }

                resized = realloc(parts, new_capacity * sizeof(*parts));
                if (resized == NULL) {
                    goto failure;
                }

                parts = resized;
                capacity = new_capacity;
            }

            if (part_length == SIZE_MAX) {
                goto failure;
            }

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

    {
        size_t part_length = input_length - start;
        char *part;

        if (count == capacity) {
            size_t new_capacity;
            char **resized;

            if (capacity == 0) {
                new_capacity = 4;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto failure;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*parts)) {
                goto failure;
            }

            resized = realloc(parts, new_capacity * sizeof(*parts));
            if (resized == NULL) {
                goto failure;
            }

            parts = resized;
            /* Possible weaknesses found:
             *  Value stored to 'capacity' is never read [deadcode.DeadStores]
             */
            capacity = new_capacity;
        }

        if (part_length == SIZE_MAX) {
            goto failure;
        }

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
    }

    *part_count = count;
    return parts;

failure:
    free_parts(parts, count);
    return NULL;
}

int main(int argc, char *argv[])
{
    const char *input;
    char **parts;
    size_t input_length;
    size_t count;
    size_t i;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program);
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