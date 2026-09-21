#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_TEXT_LENGTH 10U
#define INPUT_BUFFER_SIZE 64U
#define OUTPUT_BUFFER_SIZE (DATE_TEXT_LENGTH + 1U)

static int convert_date(const char input[static DATE_TEXT_LENGTH + 1U],
                        char output[static OUTPUT_BUFFER_SIZE],
                        size_t output_size)
{
    size_t i;

    if (output_size < OUTPUT_BUFFER_SIZE ||
        strnlen(input, DATE_TEXT_LENGTH + 1U) != DATE_TEXT_LENGTH ||
        input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (i = 0; i < DATE_TEXT_LENGTH; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    output[0] = input[8];
    output[1] = input[9];
    output[2] = '-';
    output[3] = input[5];
    output[4] = input[6];
    output[5] = '-';
    output[6] = input[0];
    output[7] = input[1];
    output[8] = input[2];
    output[9] = input[3];
    output[10] = '\0';

    return 0;
}

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char output[OUTPUT_BUFFER_SIZE];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\r\n");

    if (input[length] == '\0') {
        if (length == sizeof input - 1U) {
            if (discard_line() != 0) {
                fputs("Failed to read the date.\n", stderr);
            } else {
                fputs("Invalid date format.\n", stderr);
            }
            return EXIT_FAILURE;
        }
    } else {
        input[length] = '\0';
    }

    if (convert_date(input, output, sizeof output) != 0) {
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fprintf(stdout, "%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}