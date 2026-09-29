#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int is_self_dividing(unsigned long long number)
{
    unsigned long long remaining = number;

    if (number == 0ULL) {
        return 0;
    }

    while (remaining != 0ULL) {
        unsigned int digit = (unsigned int)(remaining % 10ULL);

        if (digit == 0U || number % digit != 0ULL) {
            return 0;
        }

        remaining /= 10ULL;
    }

    return 1;
}

static int parse_unsigned_long_long(const char *text,
                                    unsigned long long *value)
{
    char *end = NULL;
    unsigned long long result;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    result = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = result;
    return 1;
}

static void print_self_dividing_numbers(unsigned long long lower,
                                        unsigned long long upper)
{
    unsigned long long number = lower;

    for (;;) {
        if (is_self_dividing(number)) {
            printf("%llu\n", number);
        }

        if (number == upper) {
            break;
        }

        ++number;
    }
}

int main(int argc, const char *const argv[])
{
    unsigned long long lower;
    unsigned long long upper;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_unsigned_long_long(argv[1], &lower) ||
        !parse_unsigned_long_long(argv[2], &upper)) {
        fprintf(stderr, "Both bounds must be valid nonnegative integers.\n");
        return EXIT_FAILURE;
    }

    if (lower > upper) {
        fprintf(stderr, "The lower bound must not exceed the upper bound.\n");
        return EXIT_FAILURE;
    }

    print_self_dividing_numbers(lower, upper);

    if (ferror(stdout)) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}