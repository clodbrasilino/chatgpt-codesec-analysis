#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *remove_character(const char *input, size_t input_length,
                              unsigned char character)
{
    size_t output_length = 0;
    size_t i;
    size_t j = 0;
    char *output;

    if (input == NULL && input_length != 0) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
            ++output_length;
        }
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
            output[j++] = input[i];
        }
    }

    output[j] = '\0';
    return output;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return 0;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static int is_space_character(int character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
}

int main(void)
{
    char *input = NULL;
    char *result;
    size_t capacity = 0;
    size_t input_length = 0;
    int value;
    int character;

    while ((value = getchar()) != EOF && value != '\n') {
        if (input_length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        if (input_length >= capacity &&
            !grow_buffer(&input, &capacity, input_length + 1)) {
            free(input);
            return EXIT_FAILURE;
        }

        input[input_length++] = (char)(unsigned char)value;
    }

    if (ferror(stdin) || (value == EOF && input_length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    do {
        character = getchar();
        if (character == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    } while (is_space_character(character));

    result = remove_character(input, input_length,
                              (unsigned char)character);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}