#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int count_ways(size_t n, uint64_t k, uint64_t *result)
{
    uint64_t same;
    uint64_t different;

    if (result == NULL || n == 0 || k == 0) {
        return 0;
    }

    if (n == 1) {
        *result = k;
        return 1;
    }

    if (k - 1 > UINT64_MAX / k) {
        return 0;
    }

    same = k;
    different = k * (k - 1);

    for (size_t i = 3; i <= n; ++i) {
        uint64_t total;

        if (same > UINT64_MAX - different) {
            return 0;
        }

        total = same + different;

        if (k > 1 && total > UINT64_MAX / (k - 1)) {
            return 0;
        }

        same = different;
        different = total * (k - 1);
    }

    if (same > UINT64_MAX - different) {
        return 0;
    }

    *result = same + different;
    return 1;
}

static int read_values(size_t *n, uint64_t *k)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[256];
    char extra;
    uintmax_t n_value;
    uintmax_t k_value;

    if (n == NULL || k == NULL) {
        return 0;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    if (sscanf(line, " %" SCNuMAX " %" SCNuMAX " %c",
               &n_value, &k_value, &extra) != 2) {
        return 0;
    }

    if (n_value == 0 || n_value > SIZE_MAX ||
        k_value == 0 || k_value > UINT64_MAX) {
        return 0;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        return 0;
    }

    *n = (size_t)n_value;
    *k = (uint64_t)k_value;
    return 1;
}

int main(void)
{
    size_t n;
    uint64_t k;
    uint64_t result;

    if (!read_values(&n, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_ways(n, k, &result)) {
        fputs("Invalid input or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}