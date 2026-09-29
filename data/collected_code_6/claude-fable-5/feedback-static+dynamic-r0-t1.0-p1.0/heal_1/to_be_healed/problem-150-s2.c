#include <stdio.h>
#include <stdlib.h>

int is_present(long long a, long long b, long long c)
{
    long long diff;

    if (c == 0) {
        return (a == b) ? 1 : 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 - 3 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:10772,execs:6761,op:havoc,rep:7)
     */
    diff = b - a;

    if (c > 0) {
        if (diff < 0) {
            return 0;
        }
    } else {
        if (diff > 0) {
            return 0;
        }
    }

    return (diff % c == 0) ? 1 : 0;
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