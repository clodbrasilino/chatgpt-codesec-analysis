#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
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

static int get_string_length(const char *string, size_t *length)
{
    size_t count = 0;

    if (string == NULL || length == NULL) {
        return -1;
    }

    while (string[count] != '\0') {
        if (count == SIZE_MAX - 1) {
            return -1;
        }
        ++count;
    }

    *length = count;
    return 0;
}

int reverse_words(char *string, size_t length)
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
    char *string;
    size_t length;
    size_t index;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    if (get_string_length(argv[1], &length) != 0) {
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (index = 0; index < length; ++index) {
        string[index] = argv[1][index];
    }
    string[length] = '\0';

    if (reverse_words(string, length) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (fwrite(string, 1, length, stdout) != length ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}