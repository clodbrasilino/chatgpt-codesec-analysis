#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t result = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t paired_divisor = number / divisor;

            if (result > UINT64_MAX - divisor) {
                return 0;
            }
            result += divisor;

            if (paired_divisor != divisor) {
                if (result > UINT64_MAX - paired_divisor) {
                    return 0;
                }
                result += paired_divisor;
            }
        }
    }

    *sum = result;
    return 1;
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

    return ch == '\n';
}

static int read_positive_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t parsed;
    int valid = 0;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    if (length == 0 || line[length - 1] != '\n') {
        if (!feof(stdin) && !discard_line()) {
            free(line);
            return 0;
        }
    } else {
        line[length - 1] = '\0';
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (errno != ERANGE && end != line && parsed != 0 &&
        parsed <= UINT64_MAX && line[0] != '-') {
        while (*end == ' ' || *end == '\t' || *end == '\r' ||
               *end == '\n' || *end == '\v' || *end == '\f') {
            ++end;
        }

        if (*end == '\0') {
            *value = (uint64_t)parsed;
            valid = 1;
        }
    }

    free(line);
    return valid;
}

int main(void)
{
    uint64_t number;
    uint64_t sum;

    if (fputs("Enter a positive integer: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_positive_uint64(&number)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_of_divisors(number, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}