#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int multiply_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0U && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t minimum;
    uint64_t maximum;
    uint64_t n_plus_one;
    uint64_t two_n_plus_one;
    uint64_t triangular;
    uint64_t square_sum;
    uint64_t scaled;

    if (result == NULL || width == 0U || height == 0U) {
        return 0;
    }

    minimum = width < height ? width : height;
    maximum = width < height ? height : width;

    if (!add_u64(minimum, 1U, &n_plus_one)) {
        return 0;
    }

    if (minimum > (UINT64_MAX - 1U) / 2U) {
        return 0;
    }
    two_n_plus_one = minimum * 2U + 1U;

    if ((minimum & 1U) == 0U) {
        if (!multiply_u64(minimum / 2U, n_plus_one, &triangular)) {
            return 0;
        }
    } else {
        if (!multiply_u64(minimum, n_plus_one / 2U, &triangular)) {
            return 0;
        }
    }

    if (triangular % 3U == 0U) {
        if (!multiply_u64(triangular / 3U, two_n_plus_one, &square_sum)) {
            return 0;
        }
    } else if (two_n_plus_one % 3U == 0U) {
        if (!multiply_u64(triangular, two_n_plus_one / 3U, &square_sum)) {
            return 0;
        }
    } else {
        return 0;
    }

    if (!add_u64(maximum, 1U, &n_plus_one)) {
        return 0;
    }

    if (!multiply_u64(triangular, n_plus_one, &scaled)) {
        return 0;
    }

    if (scaled < square_sum) {
        return 0;
    }

    *result = scaled - square_sum;
    return 1;
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;
    int status;

    errno = 0;
    status = scanf("%" SCNu64 " %" SCNu64, &width, &height);

    if (status != 2 || errno == ERANGE) {
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