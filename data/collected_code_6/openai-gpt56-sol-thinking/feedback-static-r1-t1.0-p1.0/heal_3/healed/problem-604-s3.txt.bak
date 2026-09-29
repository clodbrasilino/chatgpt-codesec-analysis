#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary;

        --end;
        if (begin >= end) {
            break;
        }

        temporary = string[begin];
        string[begin] = string[end];
        string[end] = temporary;
        ++begin;
    }
}

static int reverse_words(char *string)
{
    size_t length;
    size_t position = 0;

    if (string == NULL) {
        return -1;
    }

    length = strlen(string);
    reverse_range(string, 0, length);

    while (position < length) {
        size_t word_start;

        while (position < length &&
               isspace((unsigned char)string[position]) != 0) {
            ++position;
        }

        word_start = position;

        while (position < length &&
               isspace((unsigned char)string[position]) == 0) {
            ++position;
        }

        reverse_range(string, word_start, position);
    }

    return 0;
}

int main(int argc, char *argv[const])
{
    const char *input;
    char *string;
    size_t length;

    if (argc != 2) {
        const char *program_name = argc > 0 && argv[0] != NULL
                                       ? argv[0]
                                       : "reverse_words";

        if (fprintf(stderr, "Usage: %s \"string\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    input = argv[1];
    length = strlen(input);

    if (length == SIZE_MAX) {
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    memcpy(string, input, length + 1);

    if (reverse_words(string) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}