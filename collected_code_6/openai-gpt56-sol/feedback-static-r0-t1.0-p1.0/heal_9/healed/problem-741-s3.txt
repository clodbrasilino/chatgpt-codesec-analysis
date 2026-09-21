#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE (1024U * 1024U)

static bool all_characters_same(const unsigned char *data, size_t length)
{
    if (data == NULL || length == 0U) {
        return false;
    }

    const unsigned char first = data[0];

    for (size_t i = 1U; i < length; ++i) {
        if (data[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    unsigned char *input = malloc(MAX_INPUT_SIZE);
    size_t length = 0U;
    bool line_ended = false;

    if (input == NULL) {
        fputs("Unable to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < MAX_INPUT_SIZE) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            line_ended = true;
            break;
        }

        if (ch == '\n') {
            line_ended = true;
            break;
        }

        input[length++] = (unsigned char)ch;
    }

    if (!line_ended) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
        } else if (ch != '\n') {
            fputs("Input exceeds the maximum allowed size.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    if (length == 0U) {
        fputs("No input provided.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (all_characters_same(input, length)) {
        puts("All characters are the same.");
    } else {
        puts("Not all characters are the same.");
    }

    free(input);
    return EXIT_SUCCESS;
}