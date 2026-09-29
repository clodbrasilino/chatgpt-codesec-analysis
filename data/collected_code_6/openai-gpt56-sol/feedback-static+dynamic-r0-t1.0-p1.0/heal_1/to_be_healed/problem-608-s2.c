#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool nth_bell_number(size_t n, uint64_t *result)
{
    uint64_t *row = NULL;

    if (result == NULL || n > (SIZE_MAX / sizeof(*row)) - 1U) {
        return false;
    }

    row = calloc(n + 1U, sizeof(*row));
    if (row == NULL) {
        return false;
    }

    row[0] = 1U;

    for (size_t i = 1U; i <= n; ++i) {
        row[i] = row[0];

        for (size_t j = i; j > 0U; --j) {
            if (UINT64_MAX - row[j] < row[j - 1U]) {
                free(row);
                return false;
            }

            row[j - 1U] += row[j];
        }
    }

    *result = row[0];
    free(row);
    return true;
}

int main(void)
{
    uintmax_t input = 0U;
    uint64_t result = 0U;
    char trailing = '\0';

    errno = 0;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNuMAX, &input) != 1 || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (scanf(" %c", &trailing) == 1 || input > SIZE_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!nth_bell_number((size_t)input, &result)) {
        fputs("Unable to compute Bell number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}