#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != UINT64_C(0)) {
        const uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int sum_common_divisors(uint64_t a, uint64_t b, uint64_t *result)
{
    const uint64_t gcd = gcd_u64(a, b);
    uint64_t sum = UINT64_C(0);

    if (result == NULL || gcd == UINT64_C(0)) {
        return -1;
    }

    for (uint64_t divisor = UINT64_C(1);
         divisor <= gcd / divisor;
         ++divisor) {
        if (gcd % divisor == UINT64_C(0)) {
            const uint64_t paired_divisor = gcd / divisor;

            if (UINT64_MAX - sum < divisor) {
                return -1;
            }
            sum += divisor;

            if (paired_divisor != divisor) {
                if (UINT64_MAX - sum < paired_divisor) {
                    return -1;
                }
                sum += paired_divisor;
            }
        }
    }

    *result = sum;
    return 0;
}

static int parse_u64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(int argc, char *const argv[])
{
    uint64_t first;
    uint64_t second;
    uint64_t sum;

    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <positive-integer> <positive-integer>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_u64(argv[1], &first) != 0 ||
        parse_u64(argv[2], &second) != 0 ||
        first == UINT64_C(0) ||
        second == UINT64_C(0)) {
        fputs("Both arguments must be positive integers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_common_divisors(first, second, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}