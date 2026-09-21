#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_non_alphanumeric(const char *input, size_t input_length, char **output)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input_length == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_length; ++read_pos) {
        unsigned char c = (unsigned char)input[read_pos];

        if ((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
            (c >= (unsigned char)'A' && c <= (unsigned char)'Z') ||
            (c >= (unsigned char)'a' && c <= (unsigned char)'z')) {
            result[write_pos++] = (char)c;
        }
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    const char input[] = "Hello, World! 123_@#";
    char *output = NULL;

    if (remove_non_alphanumeric(input, sizeof(input) - 1, &output) != 0) {
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}