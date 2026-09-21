#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_digits(uintmax_t value, uintmax_t *result)
{
    uintmax_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    do {
        sum += value % UINTMAX_C(10);
        value /= UINTMAX_C(10);
    } while (value != 0);

    *result = sum;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t value;
    uintmax_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[0] != '\n') {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0' &&
               input[length] != '\n') {
            ++length;
        }

        if (length == sizeof input || input[length] != '\n') {
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
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    {
        const char *p = input;

        while (*p == ' ' || *p == '\t' || *p == '\n' ||
               *p == '\r' || *p == '\f' || *p == '\v') {
            ++p;
        }

        if (*p == '-') {
            return EXIT_FAILURE;
        }
    }

    if (sum_digits(value, &sum) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}