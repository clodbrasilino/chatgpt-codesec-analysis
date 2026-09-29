#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0U &&
           isdigit((unsigned char)str[length - 1U]) != 0;
}

static bool discard_remaining_input(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

int main(void)
{
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)capacity, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        puts("false");
        free(input);
        return EXIT_SUCCESS;
    }

    size_t length = 0U;

    while (length < capacity && input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (length == capacity) {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        if (discard_remaining_input()) {
            fputs("Input is too large.\n", stderr);
        } else {
            fputs("Failed to read input.\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    }

    puts(ends_with_number(input, length) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}