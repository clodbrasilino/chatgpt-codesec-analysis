#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int convert_date(const char *input, char *output, size_t output_size)
{
    static const size_t input_length = 10U;
    static const size_t required_size = 11U;
    int written;

    if (input == NULL || output == NULL || output_size < required_size) {
        return -1;
    }

    if (strnlen(input, required_size) != input_length ||
        input[4] != '-' ||
        input[7] != '-') {
        return -1;
    }

    for (size_t i = 0U; i < input_length; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    written = snprintf(output, output_size, "%.2s-%.2s-%.4s",
                       input + 8, input + 5, input);

    return written == 10 ? 0 : -1;
}

int main(int argc, const char *const argv[])
{
    char *converted;
    int result = EXIT_FAILURE;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s yyyy-mm-dd\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    converted = malloc(11U);
    if (converted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (convert_date(argv[1], converted, 11U) != 0) {
        fprintf(stderr, "Invalid date format\n");
    } else if (printf("%s\n", converted) >= 0) {
        result = EXIT_SUCCESS;
    }

    free(converted);
    return result;
}