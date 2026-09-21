#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_words_of_length(char *string, size_t capacity, size_t k)
{
    size_t read_pos = 0;
    size_t write_pos = 0;
    int need_space = 0;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    while (read_pos < capacity && string[read_pos] != '\0') {
        size_t word_start;
        size_t word_length;

        while (read_pos < capacity &&
               string[read_pos] != '\0' &&
               isspace((unsigned char)string[read_pos])) {
            ++read_pos;
        }

        if (read_pos == capacity) {
            return -1;
        }

        if (string[read_pos] == '\0') {
            break;
        }

        word_start = read_pos;

        while (read_pos < capacity &&
               string[read_pos] != '\0' &&
               !isspace((unsigned char)string[read_pos])) {
            ++read_pos;
        }

        if (read_pos == capacity) {
            return -1;
        }

        word_length = read_pos - word_start;

        if (word_length != k) {
            if (need_space) {
                if (write_pos >= capacity - 1) {
                    return -1;
                }
                string[write_pos++] = ' ';
            }

            if (word_length > capacity - 1 - write_pos) {
                return -1;
            }

            memmove(string + write_pos, string + word_start, word_length);
            write_pos += word_length;
            need_space = 1;
        }
    }

    if (write_pos >= capacity) {
        return -1;
    }

    string[write_pos] = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t parsed_k;
    size_t k;
    size_t input_length;
    size_t capacity;
    char *string;

    if (argc != 3 || argv == NULL) {
        fprintf(stderr, "Usage: program <k> <string>\n");
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[2] == NULL || argv[1][0] == '\0' ||
        argv[1][0] == '-') {
        fprintf(stderr, "Invalid word length\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_k = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == NULL || end == argv[1] ||
        *end != '\0' || parsed_k > SIZE_MAX) {
        fprintf(stderr, "Invalid word length\n");
        return EXIT_FAILURE;
    }

    k = (size_t)parsed_k;
    input_length = strnlen(argv[2], SIZE_MAX);

    if (input_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    capacity = input_length + 1;
    string = malloc(capacity);

    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memmove(string, argv[2], capacity);

    if (remove_words_of_length(string, capacity, k) != 0) {
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