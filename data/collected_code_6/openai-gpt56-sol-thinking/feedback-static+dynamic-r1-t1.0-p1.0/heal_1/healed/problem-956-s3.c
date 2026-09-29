#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

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

static enum SplitStatus append_string(char ***strings, size_t *count,
                                      size_t *capacity, const char *start,
                                      size_t length)
{
    char **resized;
    char *copy;
    size_t i;

    if (strings == NULL || count == NULL || capacity == NULL ||
        start == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (*count == *capacity) {
        size_t max_capacity = SIZE_MAX / sizeof **strings;
        size_t new_capacity;

        if (*capacity == 0) {
            if (max_capacity < 4) {
                return SPLIT_OUT_OF_MEMORY;
            }
            new_capacity = 4;
        } else if (*capacity > max_capacity / 2) {
            if (*capacity == max_capacity) {
                return SPLIT_OUT_OF_MEMORY;
            }
            new_capacity = max_capacity;
        } else {
            new_capacity = *capacity * 2;
        }

        resized = realloc(*strings, new_capacity * sizeof **strings);
        if (resized == NULL) {
            return SPLIT_OUT_OF_MEMORY;
        }

        *strings = resized;
        *capacity = new_capacity;
    }

    if (length == SIZE_MAX) {
        return SPLIT_OUT_OF_MEMORY;
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
        unsigned char character = (unsigned char)input[position];

        if (isupper(character) != 0) {
            if (position > token_start) {
                status = append_string(&parts, &count, &capacity,
                                       input + token_start,
                                       position - token_start);
                if (status != SPLIT_SUCCESS) {
                    free_string_array(parts, count);
                    return status;
                }
            }

            token_start = position;
        }

        if (position == SIZE_MAX) {
            free_string_array(parts, count);
            return SPLIT_OUT_OF_MEMORY;
        }

        ++position;
    }

    status = append_string(&parts, &count, &capacity,
                           input + token_start, position - token_start);
    if (status != SPLIT_SUCCESS) {
        free_string_array(parts, count);
        return status;
    }

    *parts_out = parts;
    *count_out = count;

    return SPLIT_SUCCESS;
}

int main(int argc, char **const argv)
{
    char **parts = NULL;
    size_t count = 0;
    size_t i;
    enum SplitStatus status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = split_at_uppercase(argv[1], &parts, &count);
    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Unable to split the string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        puts(parts[i]);
    }

    free_string_array(parts, count);
    return EXIT_SUCCESS;
}