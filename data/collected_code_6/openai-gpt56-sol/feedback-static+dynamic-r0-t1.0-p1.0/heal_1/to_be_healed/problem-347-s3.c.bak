#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t minimum;
    uint64_t maximum;
    uint64_t a;
    uint64_t b;
    uint64_t divisor;

    if (result == NULL || width == 0U || height == 0U) {
        return 0;
    }

    minimum = width < height ? width : height;
    maximum = width < height ? height : width;

    /* Possible weaknesses found:
     * UBSan: division by zero (AFL crash: id:000000,sig:06,src:000009,time:50895,execs:24316,op:havoc,rep:2)
     */
    if (minimum > UINT64_MAX / (minimum + 1U)) {
        return 0;
    }

    a = minimum * (minimum + 1U) / 2U;
    divisor = (minimum % 3U == 0U) ? 3U : 1U;

    if (a > UINT64_MAX / (2U * minimum + 1U)) {
        return 0;
    }

    b = a * (2U * minimum + 1U) / divisor;
    a /= 3U / divisor;

    if (maximum == UINT64_MAX || maximum + 1U <= minimum) {
        return 0;
    }

    if (a > UINT64_MAX / (maximum + 1U)) {
        return 0;
    }

    a *= maximum + 1U;

    if (a < b) {
        return 0;
    }

    *result = a - b;
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