#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE (1024U * 1024U)

static bool all_characters_same(const unsigned char *str, size_t length)
{
    if (str == NULL || length == 0) {
        return false;
    }

    for (size_t i = 1; i < length; ++i) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    unsigned char *input = malloc(MAX_INPUT_SIZE);
    size_t length = 0;
    int ch;

    if (input == NULL) {
        fputs("Unable to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < MAX_INPUT_SIZE &&
           (ch = fgetc(stdin)) != EOF &&
           ch != '\n') {
        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length == MAX_INPUT_SIZE) {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            fputs("Input exceeds the maximum allowed size.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (ch == EOF && length == 0) {
        fputs("No input provided.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    puts(all_characters_same(input, length)
             ? "All characters are the same."
             : "Not all characters are the same.");

    free(input);
    return EXIT_SUCCESS;
}