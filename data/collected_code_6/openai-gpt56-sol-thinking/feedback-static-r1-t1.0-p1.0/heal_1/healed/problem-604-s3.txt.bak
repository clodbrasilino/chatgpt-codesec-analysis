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

int reverse_words(char *string)
{
    size_t length;
    size_t position;

    if (string == NULL) {
        return -1;
    }

    length = strlen(string);
    reverse_range(string, 0, length);

    position = 0;
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

int main(int argc, char *const argv[])
{
    char *string;
    size_t length;
    int result;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s \"string\"\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    if (length == SIZE_MAX) {
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length + 1);

    result = reverse_words(string);
    if (result != 0) {
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