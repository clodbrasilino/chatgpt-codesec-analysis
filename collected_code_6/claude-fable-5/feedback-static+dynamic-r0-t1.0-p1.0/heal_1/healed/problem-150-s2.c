#include <stdio.h>
#include <stdlib.h>

int is_present(long long a, long long b, long long c)
{
    unsigned long long udiff;
    unsigned long long uc;

    if (c == 0) {
        return (a == b) ? 1 : 0;
    }

    if (c > 0) {
        if (b < a) {
            return 0;
        }
        udiff = (unsigned long long)b - (unsigned long long)a;
        uc = (unsigned long long)c;
    } else {
        if (b > a) {
            return 0;
        }
        udiff = (unsigned long long)a - (unsigned long long)b;
        uc = -(unsigned long long)c;
    }

    return (udiff % uc == 0ULL) ? 1 : 0;
}

int main(void)
{
    long long a;
    long long b;
    long long c;

    printf("Enter first term (a): ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }

    printf("Enter number to search (b): ");
    if (scanf("%lld", &b) != 1) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }

    printf("Enter common difference (c): ");
    if (scanf("%lld", &c) != 1) {
        fprintf(stderr, "Invalid input for c\n");
        return EXIT_FAILURE;
    }

    if (is_present(a, b, c)) {
        printf("%lld is present in the sequence\n", b);
    } else {
        printf("%lld is not present in the sequence\n", b);
    }

    return EXIT_SUCCESS;
}