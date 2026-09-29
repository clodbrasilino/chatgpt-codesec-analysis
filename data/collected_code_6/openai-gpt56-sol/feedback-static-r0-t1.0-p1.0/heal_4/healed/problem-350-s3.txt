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

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (*capacity == 0) {
        new_capacity = 128;
    } else {
        if (*capacity > SIZE_MAX / 2) {
            return 0;
        }
        new_capacity = *capacity * 2;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t input_length = 0;
    int value;
    int character;
    char *result;

    while ((value = getchar()) != EOF && value != '\n') {
        if (input_length == capacity &&
            !grow_buffer(&input, &capacity)) {
            free(input);
            return EXIT_FAILURE;
        }

        input[input_length++] = (char)(unsigned char)value;
    }

    if (value == EOF && input_length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    do {
        character = getchar();
        if (character == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    } while (character == ' ' || character == '\t' ||
             character == '\n' || character == '\r' ||
             character == '\f' || character == '\v');

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