#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SPACE_STATUS_OK = 0,
    SPACE_STATUS_INVALID_ARGUMENT,
    SPACE_STATUS_OVERFLOW,
    SPACE_STATUS_ALLOCATION_FAILURE,
    SPACE_STATUS_REGEX_FAILURE
} SpaceStatus;

static SpaceStatus ensure_capacity(char **buffer, size_t *capacity,
                                   size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return SPACE_STATUS_INVALID_ARGUMENT;
    }

    if (required <= *capacity) {
        return SPACE_STATUS_OK;
    }

    new_capacity = (*capacity == 0U) ? 16U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2U;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return SPACE_STATUS_ALLOCATION_FAILURE;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return SPACE_STATUS_OK;
}

SpaceStatus add_spaces_between_words(const char *input, char **result)
{
    const unsigned char *cursor;
    unsigned char previous = 0U;
    char *output = NULL;
    size_t output_length = 0U;
    size_t capacity = 0U;
    bool have_previous = false;
    SpaceStatus status;

    if (input == NULL || result == NULL) {
        return SPACE_STATUS_INVALID_ARGUMENT;
    }

    *result = NULL;

    status = ensure_capacity(&output, &capacity, 1U);
    if (status != SPACE_STATUS_OK) {
        return status;
    }

    cursor = (const unsigned char *)input;

    while (*cursor != '\0') {
        bool insert_space;
        size_t additional;
        size_t new_length;
        size_t required;

        insert_space = have_previous &&
                       isupper((int)*cursor) != 0 &&
                       isspace((int)previous) == 0;

        additional = insert_space ? 2U : 1U;

        if (additional > SIZE_MAX - output_length) {
            free(output);
            return SPACE_STATUS_OVERFLOW;
        }

        new_length = output_length + additional;

        if (new_length == SIZE_MAX) {
            free(output);
            return SPACE_STATUS_OVERFLOW;
        }

        required = new_length + 1U;
        status = ensure_capacity(&output, &capacity, required);
        if (status != SPACE_STATUS_OK) {
            free(output);
            return status;
        }

        if (insert_space) {
            output[output_length++] = ' ';
        }

        output[output_length++] = (char)*cursor;
        previous = *cursor;
        have_previous = true;
        ++cursor;
    }

    output[output_length] = '\0';
    *result = output;

    return SPACE_STATUS_OK;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    char *result = NULL;
    SpaceStatus status;

    program_name = (argc > 0 && argv != NULL && argv[0] != NULL)
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    status = add_spaces_between_words(argv[1], &result);
    if (status != SPACE_STATUS_OK) {
        fprintf(stderr, "Failed to process the string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}