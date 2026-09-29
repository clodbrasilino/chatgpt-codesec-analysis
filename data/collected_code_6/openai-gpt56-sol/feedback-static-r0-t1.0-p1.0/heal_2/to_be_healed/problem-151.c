#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long magnitude(long long value)
{
    if (value >= 0) {
        return (unsigned long long)value;
    }

    return (unsigned long long)(-(value + 1)) + 1ULL;
}

static unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        const unsigned long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int are_coprime(long long first, long long second)
{
    return gcd(magnitude(first), magnitude(second)) == 1ULL;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end;
    long long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    long long first;
    long long second;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer1> <integer2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(argv[1], &first) ||
        !parse_long_long(argv[2], &second)) {
        fputs("Invalid integer input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (are_coprime(first, second)) {
        puts("The numbers are co-prime.");
    } else {
        puts("The numbers are not co-prime.");
    }

    return EXIT_SUCCESS;
}