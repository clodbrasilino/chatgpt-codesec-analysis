#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    DATE_LENGTH = 10,
    INPUT_BUFFER_SIZE = DATE_LENGTH + 2,
    OUTPUT_BUFFER_SIZE = DATE_LENGTH + 1
};

static int convert_date(const char *input, size_t input_length,
                        char *output, size_t output_size)
{
    if (input == NULL || output == NULL ||
        input_length != DATE_LENGTH ||
        output_size < OUTPUT_BUFFER_SIZE) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (size_t i = 0; i < DATE_LENGTH; ++i) {
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

static int discard_remaining_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (stream == NULL) {
        return -1;
    }

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }

    return ferror(stream) ? -1 : 0;
}

static int read_date(FILE *stream, char *input, size_t input_size,
                     size_t *length)
{
    if (stream == NULL || input == NULL || length == NULL ||
        input_size < INPUT_BUFFER_SIZE ||
        input_size > (size_t)INT_MAX) {
        return -1;
    }

    input[0] = '\0';
    *length = 0;

    if (fgets(input, (int)input_size, stream) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);

    if (len > 0 && input[len - 1] == '\n') {
        input[--len] = '\0';

        if (len > 0 && input[len - 1] == '\r') {
            input[--len] = '\0';
        }

        *length = len;
        return 0;
    }

    if (len < input_size - 1) {
        if (len > 0 && input[len - 1] == '\r') {
            input[--len] = '\0';
        }

        *length = len;
        return ferror(stream) ? -1 : 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char remainder[2];

    if (fgets(remainder, sizeof remainder, stream) == NULL) {
        if (ferror(stream)) {
            return -1;
        }

        *length = len;
        return 0;
    }

    if (remainder[0] == '\n') {
        *length = len;
        return 0;
    }

    if (remainder[0] == '\r') {
        if (fgets(remainder, sizeof remainder, stream) == NULL) {
            if (ferror(stream)) {
                return -1;
            }

            *length = len;
            return 0;
        }

        if (remainder[0] == '\n') {
            *length = len;
            return 0;
        }
    }

    if (discard_remaining_line(stream) != 0) {
        return -1;
    }

    *length = len;
    return 1;
}

int main(void)
{
    char *input = malloc(INPUT_BUFFER_SIZE);
    char *output = malloc(OUTPUT_BUFFER_SIZE);

    if (input == NULL || output == NULL) {
        free(input);
        free(output);
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0;
    int read_result = read_date(stdin, input, INPUT_BUFFER_SIZE, &length);

    if (read_result < 0) {
        fputs("Failed to read the date.\n", stderr);
        free(input);
        free(output);
        return EXIT_FAILURE;
    }

    if (read_result > 0) {
        fputs("Input is too long.\n", stderr);
        free(input);
        free(output);
        return EXIT_FAILURE;
    }

    if (convert_date(input, length, output, OUTPUT_BUFFER_SIZE) != 0) {
        fputs("Invalid date format.\n", stderr);
        free(input);
        free(output);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(input);
        free(output);
        return EXIT_FAILURE;
    }

    free(input);
    free(output);
    return EXIT_SUCCESS;
}