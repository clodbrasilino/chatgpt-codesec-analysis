#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum SplitStatus {
    SPLIT_SUCCESS = 0,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_OUT_OF_MEMORY
};

static void free_string_array(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static enum SplitStatus append_string(char ***strings,
                                      size_t *count,
                                      size_t *capacity,
                                      const char *start,
                                      size_t length)
{
    char *copy;
    size_t i;

    if (strings == NULL || count == NULL || capacity == NULL ||
        start == NULL || *count > *capacity ||
        (*capacity != 0 && *strings == NULL)) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return SPLIT_OUT_OF_MEMORY;
    }

    if (*count == *capacity) {
        char **resized;
        size_t new_capacity;

        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return SPLIT_OUT_OF_MEMORY;
            }

            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*resized)) {
            return SPLIT_OUT_OF_MEMORY;
        }

        resized = realloc(*strings, new_capacity * sizeof(*resized));
        if (resized == NULL) {
            return SPLIT_OUT_OF_MEMORY;
        }

        *strings = resized;
        *capacity = new_capacity;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return SPLIT_OUT_OF_MEMORY;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = start[i];
    }

    copy[length] = '\0';
    (*strings)[*count] = copy;
    ++*count;

    return SPLIT_SUCCESS;
}

static enum SplitStatus split_at_uppercase(const char *input,
                                           char ***parts_out,
                                           size_t *count_out)
{
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t position = 0;
    size_t token_start = 0;
    enum SplitStatus status;

    if (input == NULL || parts_out == NULL || count_out == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *parts_out = NULL;
    *count_out = 0;

    while (input[position] != '\0') {
        if (isupper((unsigned char)input[position]) != 0) {
            if (position > token_start) {
                status = append_string(&parts,
                                       &count,
                                       &capacity,
                                       input + token_start,
                                       position - token_start);
                if (status != SPLIT_SUCCESS) {
                    free_string_array(parts, count);
                    return status;
                }
            }

            token_start = position;
        }

        ++position;
    }

    status = append_string(&parts,
                           &count,
                           &capacity,
                           input + token_start,
                           position - token_start);
    if (status != SPLIT_SUCCESS) {
        free_string_array(parts, count);
        return status;
    }

    *parts_out = parts;
    *count_out = count;
    return SPLIT_SUCCESS;
}

int main(int argc, char **argv)
{
    const char *program_name;
    char **parts = NULL;
    size_t count = 0;
    size_t i;
    enum SplitStatus status;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "split";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    status = split_at_uppercase(argv[1], &parts, &count);
    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Unable to split the string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
            free_string_array(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_string_array(parts, count);
    return EXIT_SUCCESS;
}