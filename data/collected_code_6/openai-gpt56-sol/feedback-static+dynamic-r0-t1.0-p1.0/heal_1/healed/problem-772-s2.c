#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_words_of_length(char *string, size_t k)
{
    char *read;
    char *write;
    int need_space = 0;

    if (string == NULL) {
        return -1;
    }

    read = string;
    write = string;

    while (*read != '\0') {
        const char *start;
        size_t length;

        while (*read != '\0' && isspace((unsigned char)*read)) {
            ++read;
        }

        if (*read == '\0') {
            break;
        }

        start = read;

        while (*read != '\0' && !isspace((unsigned char)*read)) {
            ++read;
        }

        length = (size_t)(read - start);

        if (length != k) {
            if (need_space) {
                *write++ = ' ';
            }

            memmove(write, start, length);
            write += length;
            need_space = 1;
        }
    }

    *write = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    char *end;
    unsigned long long parsed_k;
    size_t k;
    size_t input_length;
    char *string;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <k> <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[2] == NULL || argv[1][0] == '-') {
        fprintf(stderr, "Invalid argument\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_k = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || end == NULL || *end != '\0' ||
        parsed_k > SIZE_MAX) {
        fprintf(stderr, "Invalid word length\n");
        return EXIT_FAILURE;
    }

    k = (size_t)parsed_k;
    input_length = strlen(argv[2]);

    if (input_length > SIZE_MAX - 1) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(input_length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(string, argv[2], input_length);
    string[input_length] = '\0';

    if (remove_words_of_length(string, k) != 0) {
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