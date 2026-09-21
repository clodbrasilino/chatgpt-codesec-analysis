#include <stdio.h>
#include <stdlib.h>

char *replace_spaces(const char *input, size_t input_size, char replacement)
{
    size_t length = 0;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    while (length < input_size && input[length] != '\0') {
        ++length;
    }

    if (length == input_size) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = input[i] == ' ' ? replacement : input[i];
    }

    result[length] = '\0';
    return result;
}

int main(void)
{
    const char input[] = "Replace blank spaces safely";
    char *result = replace_spaces(input, sizeof input, '_');

    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}