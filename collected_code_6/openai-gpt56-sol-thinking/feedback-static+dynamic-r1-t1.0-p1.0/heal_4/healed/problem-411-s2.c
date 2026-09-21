#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CONVERT_SUCCESS,
    CONVERT_INVALID_ARGUMENT,
    CONVERT_NO_MEMORY
} ConvertStatus;

static int is_ascii_alphanumeric(unsigned char character)
{
    return (character >= (unsigned char)'A' &&
            character <= (unsigned char)'Z') ||
           (character >= (unsigned char)'a' &&
            character <= (unsigned char)'z') ||
           (character >= (unsigned char)'0' &&
            character <= (unsigned char)'9');
}

static unsigned char to_ascii_upper(unsigned char character)
{
    if (character >= (unsigned char)'a' &&
        character <= (unsigned char)'z') {
        return (unsigned char)(character -
                               ((unsigned char)'a' - (unsigned char)'A'));
    }

    return character;
}

static ConvertStatus append_character(char **buffer, size_t *capacity,
                                      size_t *length,
                                      unsigned char character)
{
    size_t required_capacity;

    if (*length > SIZE_MAX - 2) {
        return CONVERT_NO_MEMORY;
    }

    required_capacity = *length + 2;

    if (required_capacity > *capacity) {
        size_t new_capacity = *capacity;
        char *new_buffer;

        while (new_capacity < required_capacity) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required_capacity;
                break;
            }

            new_capacity *= 2;
        }

        new_buffer = realloc(*buffer, new_capacity);
        if (new_buffer == NULL) {
            return CONVERT_NO_MEMORY;
        }

        *buffer = new_buffer;
        *capacity = new_capacity;
    }

    (*buffer)[(*length)++] = (char)character;
    return CONVERT_SUCCESS;
}

ConvertStatus snake_to_camel(const char *input, char **output)
{
    const unsigned char *cursor;
    char *result;
    size_t capacity = 16;
    size_t length = 0;
    ConvertStatus status;

    if (input == NULL || output == NULL) {
        return CONVERT_INVALID_ARGUMENT;
    }

    *output = NULL;

    result = malloc(capacity);
    if (result == NULL) {
        return CONVERT_NO_MEMORY;
    }

    cursor = (const unsigned char *)input;

    while (*cursor != (unsigned char)'\0') {
        if (*cursor != (unsigned char)'_') {
            status = append_character(&result, &capacity, &length, *cursor);
            if (status != CONVERT_SUCCESS) {
                free(result);
                return status;
            }

            ++cursor;
            continue;
        }

        do {
            ++cursor;
        } while (*cursor == (unsigned char)'_');

        if (*cursor != (unsigned char)'\0' &&
            is_ascii_alphanumeric(*cursor)) {
            status = append_character(&result, &capacity, &length,
                                      to_ascii_upper(*cursor));
            if (status != CONVERT_SUCCESS) {
                free(result);
                return status;
            }

            ++cursor;
        }
    }

    result[length] = '\0';
    *output = result;

    return CONVERT_SUCCESS;
}

int main(int argc, char **argv)
{
    char *camel_case = NULL;
    ConvertStatus status;
    int output_status;

    if (argc != 2) {
        fputs("Usage: snake_to_camel snake_case_string\n", stderr);
        return EXIT_FAILURE;
    }

    status = snake_to_camel(argv[1], &camel_case);
    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    output_status = puts(camel_case);
    free(camel_case);

    return output_status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}