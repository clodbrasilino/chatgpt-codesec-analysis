#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int is_self_dividing(long long number)
{
    long long remaining;

    if (number <= 0) {
        return 0;
    }

    remaining = number;

    while (remaining > 0) {
        int digit = (int)(remaining % 10);

        if (digit == 0 || number % digit != 0) {
            return 0;
        }

        remaining /= 10;
    }

    return 1;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end;
    long long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int print_self_dividing_numbers(long long lower, long long upper)
{
    long long number = lower;

    for (;;) {
        if (is_self_dividing(number) && printf("%lld\n", number) < 0) {
            return 0;
        }

        if (number == upper) {
            break;
        }

        ++number;
    }

    return 1;
}

int main(int argc, char *const argv[])
{
    long long lower;
    long long upper;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (!parse_long_long(argv[1], &lower) ||
        !parse_long_long(argv[2], &upper)) {
        fprintf(stderr, "Both bounds must be valid integers.\n");
        return EXIT_FAILURE;
    }

    if (lower <= 0 || lower > upper) {
        fprintf(stderr,
                "The range must be positive and lower must not exceed upper.\n");
        return EXIT_FAILURE;
    }

    if (!print_self_dividing_numbers(lower, upper)) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}