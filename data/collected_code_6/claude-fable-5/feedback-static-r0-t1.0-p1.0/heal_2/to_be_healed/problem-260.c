#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

static unsigned long long addmod(unsigned long long a, unsigned long long b,
                                 unsigned long long m)
{
    a %= m;
    b %= m;
    if (a >= m - b) {
        return a - (m - b);
    }
    return a + b;
}

static unsigned long long mulmod(unsigned long long a, unsigned long long b,
                                 unsigned long long m)
{
    unsigned long long r = 0;

    a %= m;
    b %= m;

    while (b > 0) {
        if (b & 1ULL) {
            r = addmod(r, a, m);
        }
        a = addmod(a, a, m);
        b >>= 1;
    }

    return r;
}

static int parse_ull(const char *s, unsigned long long *out)
{
    char *end = NULL;
    unsigned long long v;

    errno = 0;
    v = strtoull(s, &end, 10);

    if (errno == ERANGE) {
        return -1;
    }
    if (end == s || *end != '\0') {
        return -1;
    }

    *out = v;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    unsigned long long a, b, m;

    if (argc != 4) {
        fprintf(stderr, "usage: %s <a> <b> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_ull(argv[1], &a) != 0 ||
        parse_ull(argv[2], &b) != 0 ||
        parse_ull(argv[3], &m) != 0) {
        fprintf(stderr, "error: invalid unsigned integer argument\n");
        return EXIT_FAILURE;
    }

    if (m == 0) {
        fprintf(stderr, "error: modulus must be non-zero\n");
        return EXIT_FAILURE;
    }

    printf("(%llu + %llu) mod %llu = %llu\n", a, b, m, addmod(a, b, m));
    printf("(%llu * %llu) mod %llu = %llu\n", a, b, m, mulmod(a, b, m));

    return EXIT_SUCCESS;
}