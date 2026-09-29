#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 2
  */

static unsigned long long minimum_operations(long long first, long long second)
{
    unsigned long long target;
    unsigned long long current;
    unsigned long long operations = 0;

    if (first == second) {
        return 0;
    }

    if (first > second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    target = (unsigned long long)first;
    current = (unsigned long long)second;

    while (current > target) {
        if ((current & 1ULL) != 0 && current != ULLONG_MAX) {
            ++current;
        } else {
            current /= 2;
        }
        ++operations;
    }

    return operations + target - current;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end = NULL;
    long long parsed;

    errno = 0;
    parsed = strtoll(text, &end, 10);

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
    long long first;
    long long second;

    if (scanf("%127s %127s", first_input, second_input) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(first_input, &first) ||
        !parse_long_long(second_input, &second) ||
        first < 0 ||
        second < 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}