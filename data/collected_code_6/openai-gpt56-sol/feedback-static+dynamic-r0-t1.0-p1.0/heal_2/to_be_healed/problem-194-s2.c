#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int octal_to_decimal(const char *input, uintmax_t *result)
{
    char *end;
    uintmax_t value;

    if (input == NULL || result == NULL || *input == '\0') {
        return -1;
    }

    errno = 0;
    value = strtoumax(input, &end, 8);

    if (errno == ERANGE || end == input || *end != '\0') {
        return -1;
    }

    *result = value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    uintmax_t decimal;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too long\n", stderr);
        return EXIT_FAILURE;
    }

    if (octal_to_decimal(input, &decimal) != 0) {
        fputs("Invalid octal number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}