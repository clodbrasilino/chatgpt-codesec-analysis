#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_positive_sequence(int64_t n, int64_t *result)
{
    int64_t terms;
    int64_t factor;

    if (result == NULL || n <= 0) {
        return -1;
    }

    terms = n / 2 + n % 2;
    factor = n - terms + 1;

    if (terms > INT64_MAX / factor) {
        return -1;
    }

    *result = terms * factor;
    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    int ch;

    if (value == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    if (input[0] == '\0') {
        return -1;
    }

    for (size_t i = 0; i < sizeof input; ++i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }

        if (input[i] == '\0') {
            if (i == sizeof input - 1) {
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
            if (ch != EOF) {
                do {
                    if (ch == '\n') {
                        break;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    ch = getchar();
                } while (ch != EOF);
                return -1;
            }
            break;
        }
    }

    errno = 0;
    end = NULL;
    intmax_t parsed = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    int64_t n;
    int64_t sum;

    if (read_int64(&n) != 0) {
        return EXIT_FAILURE;
    }

    if (sum_positive_sequence(n, &sum) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}