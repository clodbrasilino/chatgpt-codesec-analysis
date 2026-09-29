#include <stdio.h>
#include <stdlib.h>

static long long mul_mod(long long a, long long b, long long m)
{
    long long result = 0;
    a %= m;
    if (a < 0)
        a += m;
    b %= m;
    if (b < 0)
        b += m;
    while (b > 0) {
        if (b & 1) {
            result += a;
            if (result >= m)
                result -= m;
        }
        a <<= 1;
        if (a >= m)
            a -= m;
        b >>= 1;
    }
    return result;
}

int main(int argc, const char *argv[])
{
    long long a, b, m;

    if (argc == 4) {
        a = strtoll(argv[1], NULL, 10);
        b = strtoll(argv[2], NULL, 10);
        m = strtoll(argv[3], NULL, 10);
    } else {
        if (scanf("%lld %lld %lld", &a, &b, &m) != 3) {
            fprintf(stderr, "Usage: %s a b m\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (m <= 0) {
        fprintf(stderr, "Modulus must be positive\n");
        return EXIT_FAILURE;
    }

    printf("(%lld * %lld) mod %lld = %lld\n", a, b, m, mul_mod(a, b, m));

    return EXIT_SUCCESS;
}