#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_non_alphanumeric(const char *input, size_t input_length)
{
    char *output;
    size_t read_position;
    size_t write_position = 0;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_position = 0; read_position < input_length; ++read_position) {
        unsigned char c = (unsigned char)input[read_position];

        if ((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
            (c >= (unsigned char)'A' && c <= (unsigned char)'Z') ||
            (c >= (unsigned char)'a' && c <= (unsigned char)'z')) {
            output[write_position++] = (char)c;
        }
    }

    output[write_position] = '\0';
    return output;
}

int main(void)
{
    static const char input[] = "Hello, World! 123_+-";
    char *result = remove_non_alphanumeric(input, sizeof(input) - 1);

    if (result == NULL) {
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}