#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_INPUT_SIZE 128
#define DATE_TEXT_LENGTH 10
#define DATE_OUTPUT_SIZE (DATE_TEXT_LENGTH + 1)

static int convert_date(const char input[static DATE_TEXT_LENGTH + 1],
                        char output[static DATE_OUTPUT_SIZE],
                        size_t output_size)
{
    size_t input_length;

    if (output_size < DATE_OUTPUT_SIZE) {
        return -1;
    }

    input_length = strnlen(input, DATE_TEXT_LENGTH + 1);

    if (input_length != DATE_TEXT_LENGTH ||
        input[4] != '-' ||
        input[7] != '-' ||
        input[0] < '0' || input[0] > '9' ||
        input[1] < '0' || input[1] > '9' ||
        input[2] < '0' || input[2] > '9' ||
        input[3] < '0' || input[3] > '9' ||
        input[5] < '0' || input[5] > '9' ||
        input[6] < '0' || input[6] > '9' ||
        input[8] < '0' || input[8] > '9' ||
        input[9] < '0' || input[9] > '9') {
        return -1;
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

int main(void)
{
    char input[DATE_INPUT_SIZE];
    char output[DATE_OUTPUT_SIZE];
    size_t newline_index;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    newline_index = strcspn(input, "\r\n");

    if (newline_index < sizeof input && input[newline_index] != '\0') {
        int first_newline = (unsigned char)input[newline_index];

        input[newline_index] = '\0';

        if (first_newline == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
        }
    } else if (newline_index == sizeof input - 1) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (convert_date(input, output, sizeof output) != 0) {
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}