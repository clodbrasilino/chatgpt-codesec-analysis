#include <stdio.h>
#include <stdlib.h>

static unsigned long long gcd_ull(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        unsigned long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static int count_sequences(unsigned int n, unsigned long long *result)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'num' can be reduced. [variableScope]
     */
    unsigned long long num;
    /* Possible weaknesses found:
     *  The scope of the variable 'den' can be reduced. [variableScope]
     */
    unsigned long long den;
    /* Possible weaknesses found:
     *  The scope of the variable 'g' can be reduced. [variableScope]
     */
    unsigned long long g;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    *result = 1ULL;

    for (i = 1U; i <= n; i++) {
        num = (unsigned long long)(n + i);
        den = (unsigned long long)i;

        g = gcd_ull(num, den);
        num /= g;
        den /= g;

        g = gcd_ull(*result, den);
        if (g == 0ULL) {
            return -1;
        }
        den /= g;

        if (den != 1ULL) {
            return -1;
        }

        if (num != 0ULL && *result / g > (unsigned long long)-1 / num) {
            return -1;
        }

        *result = (*result / g) * num;
    }

    return 0;
}

int main(void)
{
    unsigned int n;
    unsigned long long count;
    int scan_status;

    printf("Enter n: ");

    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 32U) {
        fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }

    if (count_sequences(n, &count) != 0) {
        fprintf(stderr, "Computation failed due to overflow\n");
        return EXIT_FAILURE;
    }

    printf("Count of binary sequences: %llu\n", count);

    return EXIT_SUCCESS;
}