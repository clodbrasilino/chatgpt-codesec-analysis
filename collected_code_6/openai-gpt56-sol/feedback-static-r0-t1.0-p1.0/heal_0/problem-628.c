#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *replace_spaces(const char *input)
{
    size_t length;
    size_t spaces = 0;
    size_t output_length;
    char *output;
    size_t i;
    size_t j = 0;

    if (input == NULL) {
        return NULL;
    }

    length = strlen(input);

    for (i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (spaces > (SIZE_MAX - length - 1U) / 2U) {
        return NULL;
    }

    output_length = length + (spaces * 2U);
    output = malloc(output_length + 1U);

    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            output[j++] = '%';
            output[j++] = '2';
            output[j++] = '0';
        } else {
            output[j++] = input[i];
        }
    }

    output[j] = '\0';
    return output;
}

int main(void)
{
    const char input[] = "Replace all spaces in this string";
    char *result = replace_spaces(input);

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