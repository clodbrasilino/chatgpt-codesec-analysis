#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_TEXT_LENGTH 10U
#define INPUT_BUFFER_SIZE 64U
#define OUTPUT_BUFFER_SIZE (DATE_TEXT_LENGTH + 1U)

static int convert_date(const char *input, char *output, size_t output_size)
{
    size_t i;
    int result;

    if (input == NULL || output == NULL ||
        output_size < OUTPUT_BUFFER_SIZE ||
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        strlen(input) != DATE_TEXT_LENGTH ||
        input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (i = 0U; i < DATE_TEXT_LENGTH; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    result = snprintf(output, output_size, "%.2s-%.2s-%.4s",
                      input + 8, input + 5, input);

    return result == (int)DATE_TEXT_LENGTH ? 0 : -1;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char *input = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_BUFFER_SIZE];
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                free(input);
                fputs("Failed to read the date.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }

        if (length >= INPUT_BUFFER_SIZE - 1U) {
            if (discard_line() != 0) {
                fputs("Failed to read the date.\n", stderr);
            } else {
                fputs("Invalid date format.\n", stderr);
            }
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            new_capacity = capacity == 0U ? 16U : capacity * 2U;
            if (new_capacity > INPUT_BUFFER_SIZE) {
                new_capacity = INPUT_BUFFER_SIZE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to read the date.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        free(input);
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            fputs("Failed to read the date.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (convert_date(input, output, sizeof output) != 0) {
        free(input);
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (fprintf(stdout, "%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}