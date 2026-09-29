#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_TEXT_LENGTH 10
#define DATE_BUFFER_SIZE (DATE_TEXT_LENGTH + 2)

static int convert_date(const char *input, size_t input_size,
                        char *output, size_t output_size)
{
    size_t i;
    size_t input_length;

    if (input == NULL || output == NULL ||
        input_size < DATE_TEXT_LENGTH + 1 ||
        output_size < DATE_TEXT_LENGTH + 1) {
        return -1;
    }

    input_length = strnlen(input, input_size);

    if (input_length != DATE_TEXT_LENGTH ||
        input[4] != '-' ||
        input[7] != '-') {
        return -1;
    }

    for (i = 0; i < DATE_TEXT_LENGTH; ++i) {
        if (i != 4 && i != 7 &&
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

int main(void)
{
    char input[DATE_BUFFER_SIZE];
    char output[DATE_TEXT_LENGTH + 1];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\r\n");

    if (input[length] == '\0') {
        if (length == sizeof input - 1) {
            int ch = getchar();

            if (ch != '\n' && ch != EOF) {
                while (ch != '\n' && ch != EOF) {
                    ch = getchar();
                }

                fputs("Invalid date format.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    } else {
        int terminator = (unsigned char)input[length];

        input[length] = '\0';

        if (terminator == '\r') {
            int ch = getchar();

            if (ch != '\n' && ch != EOF) {
                ungetc(ch, stdin);
            }
        }
    }

    if (convert_date(input, sizeof input, output, sizeof output) != 0) {
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fprintf(stdout, "%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}