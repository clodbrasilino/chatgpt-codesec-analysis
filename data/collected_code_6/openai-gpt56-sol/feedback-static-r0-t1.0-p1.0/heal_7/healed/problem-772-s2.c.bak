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
    int pending_space = 0;

    if (string == NULL) {
        return -1;
    }

    read = string;
    write = string;

    while (*read != '\0') {
        char *start;
        size_t length = 0;

        while (*read != '\0' && isspace((unsigned char)*read)) {
            pending_space = (write != string);
            ++read;
        }

        if (*read == '\0') {
            break;
        }

        start = read;

        while (*read != '\0' && !isspace((unsigned char)*read)) {
            ++read;
            ++length;
        }

        if (length != k) {
            if (pending_space) {
                *write++ = ' ';
            }

            memmove(write, start, length);
            write += length;
            pending_space = 1;
        }
    }

    *write = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long parsed_k;
    size_t k;
    size_t input_length;
    char *string;
    const char *const k_argument = argc > 1 ? argv[1] : NULL;
    const char *const input = argc > 2 ? argv[2] : NULL;
    const char *const program =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <k> <string>\n", program);
        return EXIT_FAILURE;
    }

    if (k_argument == NULL || input == NULL || k_argument[0] == '-') {
        fprintf(stderr, "Invalid argument\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_k = strtoul(k_argument, &end, 10);

    if (errno == ERANGE || end == k_argument || *end != '\0' ||
        parsed_k > SIZE_MAX) {
        fprintf(stderr, "Invalid word length\n");
        return EXIT_FAILURE;
    }

    k = (size_t)parsed_k;
    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(input_length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(string, input, input_length + 1);

    if (remove_words_of_length(string, k) != 0) {
        fprintf(stderr, "Failed to process input\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", string) < 0) {
        fprintf(stderr, "Output failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}