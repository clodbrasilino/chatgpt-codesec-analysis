#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uint64_t *decimal)
{
    uint64_t value = 0;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        return 0;
    }

    while (*binary != '\0') {
        uint64_t bit;

        if (*binary != '0' && *binary != '1') {
            return 0;
        }

        bit = (uint64_t)(*binary - '0');

        if (value > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        value = value * UINT64_C(2) + bit;
        ++binary;
    }

    *decimal = value;
    return 1;
}

static int read_binary(char **input)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[66];
    size_t length;

    if (input == NULL) {
        return 0;
    }

    *input = NULL;

    errno = 0;
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        if (ferror(stdin)) {
            if (errno != 0) {
                perror("Failed to read input");
            } else {
                fputs("Failed to read input\n", stderr);
            }
        } else {
            fputs("No input provided\n", stderr);
        }
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' &&
           buffer[length] != '\n' &&
           buffer[length] != '\r') {
        ++length;
    }

    if (buffer[length] == '\0') {
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

            if (ch == EOF && ferror(stdin)) {
                perror("Failed to read input");
            } else {
                fputs("Input is too long\n", stderr);
            }
            return 0;
        }

        if (ch == EOF && ferror(stdin)) {
            perror("Failed to read input");
            return 0;
        }
    }

    if (length == 0) {
        fputs("No input provided\n", stderr);
        return 0;
    }

    buffer[length] = '\0';

    *input = malloc(length + 1);
    if (*input == NULL) {
        perror("Failed to allocate input buffer");
        return 0;
    }

    for (size_t i = 0; i <= length; ++i) {
        (*input)[i] = buffer[i];
    }

    return 1;
}

int main(void)
{
    char *input = NULL;
    uint64_t decimal;

    if (!read_binary(&input)) {
        return EXIT_FAILURE;
    }

    if (!binary_to_decimal(input, &decimal)) {
        fputs("Invalid or out-of-range binary number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}