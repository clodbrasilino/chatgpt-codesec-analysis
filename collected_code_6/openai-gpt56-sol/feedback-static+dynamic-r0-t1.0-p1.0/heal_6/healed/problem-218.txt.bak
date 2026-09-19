#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long minimum_operations(unsigned long long first,
                                             unsigned long long second)
{
    unsigned long long operations = 0;

    while (second > first) {
        if ((second & 1ULL) != 0) {
            --second;
        } else {
            second /= 2;
        }
        ++operations;
    }

    return operations + first - second;
}

static int parse_unsigned_long_long(const char *text,
                                    unsigned long long *value)
{
    char *end;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    char first_input[128];
    char second_input[128];
    char extra_input[2];
    unsigned long long first;
    unsigned long long second;

    if (scanf("%127s %127s", first_input, second_input) != 2 ||
        scanf("%1s", extra_input) == 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_unsigned_long_long(first_input, &first) ||
        !parse_unsigned_long_long(second_input, &second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}