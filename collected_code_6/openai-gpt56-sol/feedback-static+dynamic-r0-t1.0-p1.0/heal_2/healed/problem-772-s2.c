#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int remove_words_of_length(char *string, size_t string_size, size_t k)
{
    size_t read_pos = 0;
    size_t write_pos = 0;
    int need_space = 0;

    if (string == NULL || string_size == 0) {
        return -1;
    }

    while (read_pos < string_size && string[read_pos] != '\0') {
        size_t start;
        size_t length;

        while (read_pos < string_size &&
               string[read_pos] != '\0' &&
               isspace((unsigned char)string[read_pos])) {
            ++read_pos;
        }

        if (read_pos == string_size) {
            return -1;
        }

        if (string[read_pos] == '\0') {
            break;
        }

        start = read_pos;

        while (read_pos < string_size &&
               string[read_pos] != '\0' &&
               !isspace((unsigned char)string[read_pos])) {
            ++read_pos;
        }

        if (read_pos == string_size) {
            return -1;
        }

        length = read_pos - start;

        if (length != k) {
            size_t i;

            if (need_space) {
                if (write_pos >= string_size - 1) {
                    return -1;
                }
                string[write_pos++] = ' ';
            }

            if (length > string_size - 1 - write_pos) {
                return -1;
            }

            for (i = 0; i < length; ++i) {
                string[write_pos + i] = string[start + i];
            }

            write_pos += length;
            need_space = 1;
        }
    }

    if (write_pos >= string_size) {
        return -1;
    }

    string[write_pos] = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long parsed_k;
    size_t k;
    size_t input_length = 0;
    size_t allocation_size;
    char *string;
    size_t i;

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <k> <string>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid word length\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_k = strtoull(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        parsed_k > (unsigned long long)SIZE_MAX) {
        fprintf(stderr, "Invalid word length\n");
        return EXIT_FAILURE;
    }

    k = (size_t)parsed_k;

    while (argv[2][input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    allocation_size = input_length + 1;
    string = malloc(allocation_size);

    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < input_length; ++i) {
        string[i] = argv[2][i];
    }
    string[input_length] = '\0';

    if (remove_words_of_length(string, allocation_size, k) != 0) {
        fprintf(stderr, "Failed to process input\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        fprintf(stderr, "Output failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}