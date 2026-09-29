#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_TEXT_LENGTH 10U
#define INPUT_BUFFER_SIZE 64U
#define OUTPUT_BUFFER_SIZE (DATE_TEXT_LENGTH + 1U)

static int convert_date(const char *input, size_t input_length,
                        char *output, size_t output_size)
{
    size_t i;
    int result;

    if (input == NULL || output == NULL ||
        input_length != DATE_TEXT_LENGTH ||
        output_size < OUTPUT_BUFFER_SIZE ||
        input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (i = 0U; i < DATE_TEXT_LENGTH; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    result = snprintf(output, output_size, "%c%c-%c%c-%c%c%c%c",
                      input[8], input[9],
                      input[5], input[6],
                      input[0], input[1], input[2], input[3]);

    return result == (int)DATE_TEXT_LENGTH ? 0 : -1;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char output[OUTPUT_BUFFER_SIZE];
    size_t length = 0U;
    int ch = EOF;
    int too_long = 0;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    fputs("Failed to read the date.\n", stderr);
                    return EXIT_FAILURE;
                }
            }
            break;
        }

        if (length >= sizeof input - 1U) {
            too_long = 1;
            break;
        }

        input[length++] = (char)ch;
    }

    if (too_long) {
        if (discard_line() != 0) {
            fputs("Failed to read the date.\n", stderr);
        } else {
            fputs("Invalid date format.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (convert_date(input, length, output, sizeof output) != 0) {
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fprintf(stdout, "%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}