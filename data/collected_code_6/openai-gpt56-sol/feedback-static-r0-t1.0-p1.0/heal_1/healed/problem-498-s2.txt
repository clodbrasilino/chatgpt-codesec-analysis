#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long gcd(unsigned long a, unsigned long b)
{
    while (b != 0UL) {
        const unsigned long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int parse_positive_integer(const char *text, unsigned long *value)
{
    char *end = NULL;
    unsigned long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoul(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed == 0UL) {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(int argc, char *const argv[])
{
    unsigned long a;
    unsigned long b;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive integer> <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_positive_integer(argv[1], &a) ||
        !parse_positive_integer(argv[2], &b)) {
        fputs("Both arguments must be valid positive integers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lu\n", gcd(a, b)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}