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

static int append_part(char ***parts, size_t *count, size_t *capacity,
                       const char *input, size_t start, size_t length)
{
    char *part;

    if (*count == *capacity) {
        size_t new_capacity;
        char **resized;

        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(**parts)) {
            return 0;
        }

        resized = realloc(*parts, new_capacity * sizeof(**parts));
        if (resized == NULL) {
            return 0;
        }

        *parts = resized;
        *capacity = new_capacity;
    }

    if (length > SIZE_MAX - 1) {
        return 0;
    }

    part = malloc(length + 1);
    if (part == NULL) {
        return 0;
    }

    if (length != 0) {
        memcpy(part, input + start, length);
    }
    part[length] = '\0';

    (*parts)[*count] = part;
    ++*count;

    return 1;
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
            if (!append_part(&parts, &count, &capacity, input, start,
                             i - start)) {
                free_parts(parts, count);
                return NULL;
            }
            start = i;
        }
    }

    if (!append_part(&parts, &count, &capacity, input, start,
                     input_length - start)) {
        free_parts(parts, count);
        return NULL;
    }

    *part_count = count;
    return parts;
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