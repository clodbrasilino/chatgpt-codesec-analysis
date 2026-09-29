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
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + 6, input, 4);
    output[10] = '\0';

    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_date(char *input, size_t input_size, size_t *length)
{
    if (input == NULL || length == NULL ||
        input_size < INPUT_BUFFER_SIZE) {
        return -1;
    }

    *length = 0;

    if (fgets(input, (int)input_size, stdin) == NULL) {
        return -1;
    }

    size_t len = strcspn(input, "\r\n");

    if (input[len] == '\r' || input[len] == '\n') {
        /* Possible weaknesses found:
         *  Assignment 'input[len]='\0'', assigned value is 0
         */
        input[len] = '\0';
        *length = len;

        /* Possible weaknesses found:
         *  Condition 'input[len]=='\r'' is always false [knownConditionTrueFalse]
         *  Condition 'input[len]=='\r'' is always false
         */
        if (input[len] == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int ch = getchar();

            if (ch != '\n' && ch != EOF) {
                ungetc(ch, stdin);
            } else if (ch == EOF && ferror(stdin)) {
                return -1;
            }
        }

        return 0;
    }

    *length = len;

    if (len == DATE_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n') {
            return 0;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();

            if (ch == '\n' || (ch == EOF && !ferror(stdin))) {
                return 0;
            }
        }

        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    }

    return discard_line() == 0 ? 1 : -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_BUFFER_SIZE];
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