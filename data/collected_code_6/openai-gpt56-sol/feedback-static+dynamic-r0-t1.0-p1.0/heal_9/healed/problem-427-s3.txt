#include <stdio.h>
#include <stdlib.h>

#define DATE_TEXT_LENGTH 10U
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

static int read_date(char *buffer, size_t capacity, size_t *length)
{
    int ch;
    size_t used = 0U;
    int overflow = 0;

    if (buffer == NULL || length == NULL || capacity == 0U) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            ch = fgetc(stdin);
            if (ch != '\n' && ch != EOF) {
                overflow = 1;
                while (ch != '\n' && ch != EOF) {
                    ch = fgetc(stdin);
                }
            }
            break;
        }

        if (used + 1U < capacity) {
            buffer[used++] = (char)ch;
        } else {
            overflow = 1;
        }
    }

    if (ferror(stdin)) {
        return -1;
    }

    if (ch == EOF && used == 0U) {
        return -1;
    }

    buffer[used] = '\0';
    *length = used;

    return overflow ? 1 : 0;
}

int main(void)
{
    char input[DATE_TEXT_LENGTH + 1U];
    char output[OUTPUT_BUFFER_SIZE];
    size_t length;
    int status;

    status = read_date(input, sizeof input, &length);
    if (status < 0) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0 ||
        convert_date(input, length, output, sizeof output) != 0) {
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(output, stdout) == EOF || fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}