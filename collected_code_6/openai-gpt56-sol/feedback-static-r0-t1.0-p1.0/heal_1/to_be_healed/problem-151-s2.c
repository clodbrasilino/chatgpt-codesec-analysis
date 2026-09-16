#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    while (b != 0U) {
        const unsigned long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static bool are_coprime(long long first, long long second)
{
    const unsigned long long a =
        first < 0 ? 0ULL - (unsigned long long)first : (unsigned long long)first;
    const unsigned long long b =
        second < 0 ? 0ULL - (unsigned long long)second : (unsigned long long)second;

    return gcd(a, b) == 1U;
}

static bool parse_integer(const char *text, long long *value)
{
    char *end = NULL;
    long long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return false;
    }

    errno = 0;
    parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return false;
    }

    *value = parsed;
    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    long long first;
    long long second;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer1> <integer2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_integer(argv[1], &first) || !parse_integer(argv[2], &second)) {
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