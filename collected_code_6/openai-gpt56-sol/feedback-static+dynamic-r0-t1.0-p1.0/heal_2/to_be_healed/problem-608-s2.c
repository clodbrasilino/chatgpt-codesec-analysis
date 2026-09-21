#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static bool nth_bell_number(size_t n, uint64_t *result)
{
    if (result == NULL || n == SIZE_MAX ||
        n + 1U > SIZE_MAX / sizeof(uint64_t)) {
        return false;
    }

    uint64_t *row = calloc(n + 1U, sizeof(*row));
    if (row == NULL) {
        return false;
    }

    row[0] = UINT64_C(1);

    for (size_t i = 1U; i <= n; ++i) {
        row[i] = row[0];

        for (size_t j = i; j > 0U; --j) {
            if (row[j - 1U] > UINT64_MAX - row[j]) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char extra;
    uintmax_t input;
    uint64_t result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end;
    input = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || input > SIZE_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(buffer, '\n') == NULL &&
        fread(&extra, 1U, 1U, stdin) == 1U) {
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