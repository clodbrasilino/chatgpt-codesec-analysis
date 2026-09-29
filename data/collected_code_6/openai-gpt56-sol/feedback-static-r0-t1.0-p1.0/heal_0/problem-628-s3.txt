#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_spaces(const char *input)
{
    size_t length;
    size_t spaces = 0;
    size_t output_length;
    char *output;
    char *destination;

    if (input == NULL) {
        return NULL;
    }

    length = strlen(input);

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (spaces > (SIZE_MAX - length - 1) / 2) {
        return NULL;
    }

    output_length = length + (spaces * 2);
    output = malloc(output_length + 1);

    if (output == NULL) {
        return NULL;
    }

    destination = output;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            *destination++ = '%';
            *destination++ = '2';
            *destination++ = '0';
        } else {
            *destination++ = input[i];
        }
    }

    *destination = '\0';
    return output;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (length == sizeof(input) - 1) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    char *result = replace_spaces(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to replace spaces.\n");
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}