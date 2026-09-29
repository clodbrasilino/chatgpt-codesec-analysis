#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    DATE_LENGTH = 10,
    INPUT_BUFFER_SIZE = 128,
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

    int written = snprintf(output, output_size, "%.2s-%.2s-%.4s",
                           input + 8, input + 5, input);

    return written == DATE_LENGTH ? 0 : -1;
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

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\0') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
    } else {
        char terminator = input[length];
        input[length] = '\0';

        if (terminator == '\r' && input[length + 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
                }

                fputs("Invalid input.\n", stderr);
                return EXIT_FAILURE;
            }
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