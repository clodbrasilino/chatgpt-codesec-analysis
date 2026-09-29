#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return -1;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return -1;
    }

    a *= b;

    if (a != 0 && a > UINT64_MAX / a) {
        return -1;
    }

    a *= a;

    if (a > UINT64_MAX / UINT64_C(2)) {
        return -1;
    }

    *result = a * UINT64_C(2);
    return 0;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;
    size_t i = 0;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    while (buffer[i] != '\0' && buffer[i] != '\n') {
        ++i;
    }

    if (buffer[i] != '\n') {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return -1;
    }

    buffer[i] = '\0';

    end = buffer;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '\0' || *end == '+' || *end == '-') {
        return -1;
    }

    /* Possible weaknesses found:
     *  'errno' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    errno = 0;
    parsed = strtoumax(end, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'ERANGE'
     *  use of undeclared identifier 'errno'
     */
    if (errno == ERANGE || parsed > (uintmax_t)UINT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (read_uint64(&n) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_sum_even(n, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}