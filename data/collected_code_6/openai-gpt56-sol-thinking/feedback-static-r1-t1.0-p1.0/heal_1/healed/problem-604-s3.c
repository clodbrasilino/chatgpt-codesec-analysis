#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

static int reverse_words(char *string, size_t length)
{
    size_t position = 0;

    if (string == NULL) {
        return -1;
    }

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

int main(int argc, char *argv[])
{
    const char *program_name;
    size_t length = 0;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s \"string\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    while (argv[1][length] != '\0') {
        ++length;
    }

    if (reverse_words(argv[1], length) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}