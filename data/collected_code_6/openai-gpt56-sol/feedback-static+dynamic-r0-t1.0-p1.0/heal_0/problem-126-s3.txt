#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int sum_common_divisors(uint64_t a, uint64_t b, uint64_t *result)
{
    uint64_t gcd;
    uint64_t sum = 0U;

    if (result == NULL || a == 0U || b == 0U) {
        return -1;
    }

    gcd = gcd_u64(a, b);

    for (uint64_t divisor = 1U; divisor <= gcd / divisor; ++divisor) {
        if (gcd % divisor == 0U) {
            uint64_t paired_divisor = gcd / divisor;

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

static int parse_positive_u64(const char *text, uint64_t *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '\0' || text[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed == 0U) {
        return -1;
    }

#if ULLONG_MAX > UINT64_MAX
    if (parsed > UINT64_MAX) {
        return -1;
    }
#endif

    *value = (uint64_t)parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    uint64_t first;
    uint64_t second;
    uint64_t sum;

    if (argc != 3) {
        (void)fprintf(stderr, "Usage: %s <positive integer> <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_positive_u64(argv[1], &first) != 0 ||
        parse_positive_u64(argv[2], &second) != 0) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_common_divisors(first, second, &sum) != 0) {
        (void)fprintf(stderr, "Unable to calculate the sum\n");
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", (unsigned long long)sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}