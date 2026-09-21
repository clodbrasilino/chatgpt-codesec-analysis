#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int checked_add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_mul_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t minimum;
    uint64_t maximum;
    uint64_t minimum_plus_one;
    uint64_t maximum_plus_one;
    uint64_t twice_minimum;
    uint64_t factor1;
    uint64_t factor2;
    uint64_t factor3;
    uint64_t sum;
    uint64_t product;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    minimum = width < height ? width : height;
    maximum = width < height ? height : width;

    if (!checked_add_u64(minimum, UINT64_C(1), &minimum_plus_one) ||
        !checked_add_u64(maximum, UINT64_C(1), &maximum_plus_one) ||
        !checked_mul_u64(minimum, UINT64_C(2), &twice_minimum) ||
        !checked_add_u64(twice_minimum, UINT64_C(1), &factor3)) {
        return 0;
    }

    factor1 = minimum;
    factor2 = minimum_plus_one;

    if ((factor1 & UINT64_C(1)) == 0) {
        factor1 /= UINT64_C(2);
    } else {
        factor2 /= UINT64_C(2);
    }

    if (factor1 % UINT64_C(3) == 0) {
        factor1 /= UINT64_C(3);
    } else if (factor2 % UINT64_C(3) == 0) {
        factor2 /= UINT64_C(3);
    } else {
        factor3 /= UINT64_C(3);
    }

    if (!checked_mul_u64(factor1, factor2, &product) ||
        !checked_mul_u64(product, factor3, &sum)) {
        return 0;
    }

    factor1 = minimum;
    factor2 = minimum_plus_one;

    if ((factor1 & UINT64_C(1)) == 0) {
        factor1 /= UINT64_C(2);
    } else {
        factor2 /= UINT64_C(2);
    }

    if (!checked_mul_u64(factor1, factor2, &product) ||
        !checked_mul_u64(product, maximum_plus_one, &product) ||
        product < sum) {
        return 0;
    }

    *result = product - sum;
    return 1;
}

static int read_input(uint64_t *width, uint64_t *height)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char extra;
    uintmax_t parsed_width;
    uintmax_t parsed_height;
    int matched;
    int ch;

    if (width == NULL || height == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(buffer, '\n') == NULL) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return 0;
        }

        if (ferror(stdin)) {
            return 0;
        }
    }

    matched = sscanf(buffer, " %" SCNuMAX " %" SCNuMAX " %c",
                     &parsed_width, &parsed_height, &extra);

    if (matched != 2 || parsed_width > UINT64_MAX ||
        parsed_height > UINT64_MAX) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    if (ferror(stdin)) {
        return 0;
    }

    *width = (uint64_t)parsed_width;
    *height = (uint64_t)parsed_height;
    return 1;
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (!read_input(&width, &height)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}