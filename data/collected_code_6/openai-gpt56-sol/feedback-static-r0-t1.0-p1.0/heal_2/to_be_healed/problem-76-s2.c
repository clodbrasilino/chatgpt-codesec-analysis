#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

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

static int triangular_u64(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL) {
        return 0;
    }

    a = n;
    b = n + 1;

    if ((a & 1U) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    return checked_mul_u64(a, b, result);
}

static int sum_squares_u64(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t product;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + 1;
    if (n > (UINT64_MAX - 1) / 2) {
        return 0;
    }
    c = 2 * n + 1;

    if ((a & 1U) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a % 3 == 0) {
        a /= 3;
    } else if (b % 3 == 0) {
        b /= 3;
    } else {
        c /= 3;
    }

    if (!checked_mul_u64(a, b, &product)) {
        return 0;
    }

    return checked_mul_u64(product, c, result);
}

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t side;
    uint64_t other;
    uint64_t triangular;
    uint64_t square_sum;
    uint64_t factor;
    uint64_t product;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    if (width < height) {
        side = width;
        other = height;
    } else {
        side = height;
        other = width;
    }

    if (!checked_add_u64(other, 1, &factor)) {
        return 0;
    }

    if (!triangular_u64(side, &triangular) ||
        !sum_squares_u64(side, &square_sum) ||
        !checked_mul_u64(factor, triangular, &product) ||
        square_sum > product) {
        return 0;
    }

    *result = product - square_sum;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    uint64_t width;
    uint64_t height;
    uint64_t result;
    char trailing;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sscanf(input, "%" SCNu64 " %" SCNu64 " %c",
               &width, &height, &trailing) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}