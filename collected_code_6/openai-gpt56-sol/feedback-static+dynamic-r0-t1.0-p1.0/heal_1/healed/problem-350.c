#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_CAPACITY 4096

char *remove_character(const char *input, size_t input_length, char character)
{
    char *output;
    size_t read_index;
    size_t write_index = 0;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < input_length; ++read_index) {
        if (input[read_index] != character) {
            output[write_index++] = input[read_index];
        }
    }

    output[write_index] = '\0';
    return output;
}

int main(void)
{
    char *input;
    char *character_line;
    char *result;
    size_t input_length;
    int ch;

    input = malloc(INPUT_CAPACITY);
    character_line = malloc(INPUT_CAPACITY);

    if (input == NULL || character_line == NULL) {
        free(input);
        free(character_line);
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        free(input);
        free(character_line);
        return EXIT_FAILURE;
    }

    input_length = strnlen(input, INPUT_CAPACITY);
    if (input_length == INPUT_CAPACITY) {
        free(input);
        free(character_line);
        return EXIT_FAILURE;
    }

    if (input_length > 0 && input[input_length - 1] == '\n') {
        input[--input_length] = '\0';
    } else {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    if (fgets(character_line, INPUT_CAPACITY, stdin) == NULL ||
        character_line[0] == '\0' ||
        character_line[0] == '\n') {
        free(input);
        free(character_line);
        return EXIT_FAILURE;
    }

    result = remove_character(input, input_length, character_line[0]);
    free(input);
    free(character_line);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}