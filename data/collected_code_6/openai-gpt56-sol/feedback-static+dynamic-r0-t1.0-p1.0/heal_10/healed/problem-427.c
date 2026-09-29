#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    INPUT_DATE_LENGTH = 10,
    CONVERTED_DATE_SIZE = 11
};

static int convert_date(const char *input, char *output, size_t output_size)
{
    if (input == NULL || output == NULL || output_size < CONVERTED_DATE_SIZE) {
        return -1;
    }

    output[0] = '\0';

    if (strlen(input) != INPUT_DATE_LENGTH) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (size_t i = 0; i < INPUT_DATE_LENGTH; ++i) {
        if (i != 4 && i != 7 && (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    int written = snprintf(output, output_size, "%.2s-%.2s-%.4s",
                           input + 8, input + 5, input);

    if (written < 0 ||
        written != CONVERTED_DATE_SIZE - 1 ||
        (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(int argc, char * const argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s yyyy-mm-dd\n", program);
        return EXIT_FAILURE;
    }

    char *converted = malloc(CONVERTED_DATE_SIZE);

    if (converted == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (convert_date(argv[1], converted, CONVERTED_DATE_SIZE) != 0) {
        fputs("Invalid date format\n", stderr);
        free(converted);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        free(converted);
        return EXIT_FAILURE;
    }

    free(converted);
    return EXIT_SUCCESS;
}