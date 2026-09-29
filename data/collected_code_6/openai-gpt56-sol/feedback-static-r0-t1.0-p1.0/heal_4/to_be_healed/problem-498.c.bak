#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        unsigned long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int parse_positive_integer(const char *text, unsigned long long *value)
{
    char *end;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '\0' || text[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed == 0ULL) {
        return 0;
    }

    *value = parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[const])
{
    unsigned long long first;
    unsigned long long second;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive-integer> <positive-integer>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_positive_integer(argv[1], &first) ||
        !parse_positive_integer(argv[2], &second)) {
        fputs("Both arguments must be valid positive integers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", gcd(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}