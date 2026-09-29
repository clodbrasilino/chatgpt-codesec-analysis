#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_INPUT_SIZE 128
#define DATE_OUTPUT_SIZE 11
#define DATE_LENGTH 10

static int convert_date(const char *input, size_t input_length,
                        char *output, size_t output_size)
{
    if (input == NULL || output == NULL ||
        input_length != DATE_LENGTH ||
        output_size < DATE_OUTPUT_SIZE) {
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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[DATE_INPUT_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[DATE_OUTPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = strnlen(input, sizeof input);

    if (length == sizeof input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
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