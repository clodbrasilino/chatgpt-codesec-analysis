#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int sum_even_squares(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t product;

    if (result == NULL || n > UINT64_MAX / 2U) {
        return 0;
    }

    a = n;
    b = n + 1U;
    c = (2U * n) + 1U;

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a % 3U == 0U) {
        a /= 3U;
    } else if (b % 3U == 0U) {
        b /= 3U;
    } else {
        c /= 3U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return 0;
    }

    product = a * b;

    if (product != 0U && c > UINT64_MAX / product) {
        return 0;
    }

    product *= c;

    if (product > UINT64_MAX / 4U) {
        return 0;
    }

    *result = product * 4U;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    uintmax_t value;
    uint64_t n;
    uint64_t sum;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (printf("Enter n: ") < 0) {
        return 1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        (void)fprintf(stderr, "Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        (void)fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    end = input;
    value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || value > UINT64_MAX) {
        (void)fprintf(stderr, "Invalid input\n");
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        (void)fprintf(stderr, "Invalid input\n");
        return 1;
    }

    n = (uint64_t)value;

    if (!sum_even_squares(n, &sum)) {
        (void)fprintf(stderr, "Result exceeds the supported range\n");
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}