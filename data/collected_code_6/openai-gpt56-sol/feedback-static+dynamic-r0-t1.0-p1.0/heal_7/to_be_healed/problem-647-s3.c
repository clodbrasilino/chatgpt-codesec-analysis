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

    if (input == NULL || part_count == NULL) {
        return NULL;
    }

    *part_count = 0;

    if (input_length == 0) {
        return NULL;
    }

    for (i = 1; i <= input_length; ++i) {
        if (i == input_length ||
            isupper((unsigned char)input[i]) != 0) {
            size_t part_length = i - start;
            size_t allocation_size;
            char *part;

            if (start > input_length ||
                part_length > input_length - start) {
                goto failure;
            }

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

            allocation_size = part_length + 1;
            part = malloc(allocation_size);
            if (part == NULL) {
                goto failure;
            }

            if (part_length != 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(part, input + start, part_length);
            }
            part[part_length] = '\0';

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