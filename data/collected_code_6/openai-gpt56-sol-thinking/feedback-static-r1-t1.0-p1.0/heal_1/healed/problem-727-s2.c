#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_non_alnum(const char *input, size_t input_length, char **output)
{
    char *result;
    size_t result_length = 0;
    size_t destination = 0;

    if (input == NULL || output == NULL) {
        errno = EINVAL;
        return -1;
    }

    *output = NULL;

    if (input_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return -1;
    }

    for (size_t i = 0; i < input_length; ++i) {
        if (isalnum((unsigned char)input[i]) != 0) {
            ++result_length;
        }
    }

    result = malloc(result_length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return -1;
    }

    for (size_t i = 0; i < input_length; ++i) {
        if (isalnum((unsigned char)input[i]) != 0) {
            result[destination++] = input[i];
        }
    }

    result[destination] = '\0';
    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *filtered;
    size_t input_length = 0;

    if (argc != 2) {
        if (fputs("Usage: program <text>\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            errno = EOVERFLOW;
            perror("input");
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    if (remove_non_alnum(input, input_length, &filtered) != 0) {
        perror("remove_non_alnum");
        return EXIT_FAILURE;
    }

    if (fputs(filtered, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(filtered);
        return EXIT_FAILURE;
    }

    free(filtered);
    return EXIT_SUCCESS;
}