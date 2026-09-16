#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        const unsigned long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int sum_common_divisors(unsigned long long a,
                               unsigned long long b,
                               unsigned long long *sum)
{
    unsigned long long result = 0ULL;
    const unsigned long long common_gcd = gcd(a, b);

    if (sum == NULL || a == 0ULL || b == 0ULL) {
        return -1;
    }

    for (unsigned long long divisor = 1ULL;
         divisor <= common_gcd / divisor;
         ++divisor) {
        if (common_gcd % divisor == 0ULL) {
            const unsigned long long paired_divisor = common_gcd / divisor;

            if (ULLONG_MAX - result < divisor) {
                return -1;
            }
            result += divisor;

            if (paired_divisor != divisor) {
                if (ULLONG_MAX - result < paired_divisor) {
                    return -1;
                }
                result += paired_divisor;
            }
        }
    }

    *sum = result;
    return 0;
}

static int parse_positive_integer(const char *text,
                                  unsigned long long *value)
{
    char *end = NULL;
    unsigned long long parsed_value;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed_value = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed_value == 0ULL) {
        return -1;
    }

    *value = parsed_value;
    return 0;
}

int main(int argc, char *const argv[])
{
    unsigned long long first;
    unsigned long long second;
    unsigned long long sum;
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <positive integer> <positive integer>\n",
                program_name);
        return EXIT_FAILURE;
    }

    if (argv == NULL ||
        parse_positive_integer(argv[1], &first) != 0 ||
        parse_positive_integer(argv[2], &second) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_common_divisors(first, second, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}