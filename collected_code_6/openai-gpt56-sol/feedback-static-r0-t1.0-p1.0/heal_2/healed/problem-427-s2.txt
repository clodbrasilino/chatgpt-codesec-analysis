#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int convert_date(const char *input, char *output, size_t output_size)
{
    const size_t input_length = 10U;
    const size_t required_size = 11U;
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

    if (written != 10) {
        return -1;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    char converted[11U];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s yyyy-mm-dd\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (convert_date(argv[1], converted, sizeof converted) != 0) {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}