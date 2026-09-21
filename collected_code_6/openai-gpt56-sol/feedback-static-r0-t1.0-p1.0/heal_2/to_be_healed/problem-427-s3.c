#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_INPUT_SIZE 128
#define DATE_OUTPUT_SIZE 11

static int convert_date(const char *input, char *output, size_t output_size)
{
    int result;

    if (input == NULL || output == NULL || output_size < DATE_OUTPUT_SIZE) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) != 10 ||
        input[4] != '-' ||
        input[7] != '-') {
        return -1;
    }

    for (size_t i = 0; i < 10; ++i) {
        if (i != 4 && i != 7 &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    result = snprintf(
        output,
        output_size,
        "%c%c-%c%c-%c%c%c%c",
        input[8], input[9],
        input[5], input[6],
        input[0], input[1], input[2], input[3]
    );

    if (result != DATE_OUTPUT_SIZE - 1 ||
        (size_t)result >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char *input = malloc(DATE_INPUT_SIZE);
    char *output = malloc(DATE_OUTPUT_SIZE);

    if (input == NULL || output == NULL) {
        free(input);
        free(output);
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, DATE_INPUT_SIZE, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        free(input);
        free(output);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else if (length == DATE_INPUT_SIZE - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            fputs("Input is too long.\n", stderr);
            free(input);
            free(output);
            return EXIT_FAILURE;
        }
    }

    if (convert_date(input, output, DATE_OUTPUT_SIZE) != 0) {
        fputs("Invalid date format.\n", stderr);
        free(input);
        free(output);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        free(input);
        free(output);
        return EXIT_FAILURE;
    }

    free(input);
    free(output);
    return EXIT_SUCCESS;
}