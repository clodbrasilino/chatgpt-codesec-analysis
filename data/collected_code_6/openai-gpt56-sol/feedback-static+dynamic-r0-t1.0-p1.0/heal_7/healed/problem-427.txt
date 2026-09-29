#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { CONVERTED_DATE_SIZE = sizeof("dd-mm-yyyy") };

static int convert_date(const char *input, char *output, size_t output_size)
{
    if (input == NULL || output == NULL ||
        output_size < CONVERTED_DATE_SIZE ||
        strlen(input) != sizeof("yyyy-mm-dd") - 1) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (size_t i = 0; i < sizeof("yyyy-mm-dd") - 1; ++i) {
        if (i != 4 && i != 7 &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    int result = snprintf(output, output_size, "%.2s-%.2s-%.4s",
                          input + 8, input + 5, input);

    if (result != CONVERTED_DATE_SIZE - 1) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char converted[CONVERTED_DATE_SIZE];

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s yyyy-mm-dd\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (convert_date(argv[1], converted, sizeof converted) != 0) {
        fputs("Invalid date format\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}