#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_date(char *input, size_t input_size, size_t *length)
{
    if (input == NULL || length == NULL ||
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        input_size < INPUT_BUFFER_SIZE || input_size > (size_t)INT_MAX) {
        return -1;
    }

    *length = 0;

    if (fgets(input, (int)input_size, stdin) == NULL) {
        return -1;
    }

    size_t len = strcspn(input, "\r\n");

    if (input[len] == '\n') {
        input[len] = '\0';
        *length = len;
        return 0;
    }

    if (input[len] == '\r') {
        input[len] = '\0';
        *length = len;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || (ch == EOF && !ferror(stdin))) {
            return 0;
        }

        if (ch == EOF) {
            return -1;
        }

        return discard_line() == 0 ? 1 : -1;
    }

    *length = len;

    if (len < input_size - 1) {
        return ferror(stdin) ? -1 : 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int ch = fgetc(stdin);

    if (ch == '\n' || (ch == EOF && !ferror(stdin))) {
        return 0;
    }

    if (ch == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || (ch == EOF && !ferror(stdin))) {
            return 0;
        }

        if (ch == EOF) {
            return -1;
        }
    }

    return discard_line() == 0 ? 1 : -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_BUFFER_SIZE] = {0};
    size_t length = 0;

    int read_result = read_date(input, sizeof input, &length);

    if (read_result < 0) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_result > 0) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (convert_date(input, length, output, sizeof output) != 0) {
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}