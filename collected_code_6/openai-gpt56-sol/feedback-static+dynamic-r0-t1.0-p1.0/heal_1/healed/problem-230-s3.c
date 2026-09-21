#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024U

char *replace_spaces(const char *source, size_t source_size, char replacement)
{
    const char *terminator;
    char *result;
    size_t length;
    size_t i;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        result[i] = source[i] == ' ' ? replacement : source[i];
    }

    result[length] = '\0';
    return result;
}

int main(void)
{
    char *input;
    char replacement_line[3];
    char replacement;
    char *result;
    size_t newline_index;

    input = malloc(INPUT_SIZE);
    if (input == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)INPUT_SIZE, stdin) == NULL) {
        fputs("Failed to read the string.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    newline_index = strcspn(input, "\n");
    if (input[newline_index] == '\n') {
        input[newline_index] = '\0';
    } else if (input[newline_index] != '\0') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    } else {
        int ch;

        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                ch = getchar();
            }
            fputs("Input string is too long.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (fgets(replacement_line, sizeof replacement_line, stdin) == NULL) {
        fputs("Failed to read the replacement character.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (replacement_line[0] == '\n' || replacement_line[0] == '\0' ||
        (replacement_line[1] != '\n' && replacement_line[1] != '\0')) {
        fputs("Invalid replacement character.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    replacement = replacement_line[0];
    result = replace_spaces(input, INPUT_SIZE, replacement);
    free(input);

    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}