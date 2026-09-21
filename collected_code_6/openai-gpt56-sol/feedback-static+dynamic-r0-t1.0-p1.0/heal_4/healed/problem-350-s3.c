#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

char *remove_character(const char *input, size_t input_length,
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
    char *result;
    size_t capacity = 0;
    size_t length;
    ssize_t bytes_read;
    int ch;
    unsigned char character;

    bytes_read = getline(&input, &capacity, stdin);
    if (bytes_read < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    length = (size_t)bytes_read;

    if (length > 0 && input[length - 1] == '\n') {
        --length;
        if (length > 0 && input[length - 1] == '\r') {
            --length;
        }
    }

    input[length] = '\0';

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            free(input);
            return EXIT_FAILURE;
        }

        if (ch != ' ' && ch != '\t' && ch != '\n' &&
            ch != '\r' && ch != '\f' && ch != '\v') {
            break;
        }
    }

    character = (unsigned char)ch;
    result = remove_character(input, length, character);
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