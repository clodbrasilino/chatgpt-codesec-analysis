#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static char *remove_character(const char *input, size_t input_length,
                              unsigned char character)
{
    size_t output_length = 0;
    size_t i;
    size_t j = 0;
    char *output;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
            ++output_length;
        }
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

int main(void)
{
    char *input = NULL;
    char *character_line = NULL;
    char *result;
    size_t input_capacity = 0;
    size_t character_capacity = 0;
    size_t input_length;
    size_t character_length;
    ssize_t bytes_read;
    unsigned char character;

    bytes_read = getline(&input, &input_capacity, stdin);
    if (bytes_read < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    input_length = (size_t)bytes_read;
    if (input_length > 0 && input[input_length - 1] == '\n') {
        --input_length;
        if (input_length > 0 && input[input_length - 1] == '\r') {
            --input_length;
        }
    }
    input[input_length] = '\0';

    bytes_read = getline(&character_line, &character_capacity, stdin);
    if (bytes_read < 0) {
        free(input);
        free(character_line);
        return EXIT_FAILURE;
    }

    character_length = (size_t)bytes_read;
    if (character_length > 0 &&
        character_line[character_length - 1] == '\n') {
        --character_length;
        if (character_length > 0 &&
            character_line[character_length - 1] == '\r') {
            --character_length;
        }
    }

    if (character_length != 1) {
        free(input);
        free(character_line);
        return EXIT_FAILURE;
    }

    character = (unsigned char)character_line[0];
    free(character_line);

    result = remove_character(input, input_length, character);
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