#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_undulating(long long n);

bool is_undulating(long long n)
{
    if (n < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000008,time:4160,execs:2609,op:havoc,rep:2)
         */
        n = -n;
    }

    if (n < 100) {
        return false;
    }

    int a = (int)(n % 10);
    n /= 10;
    int b = (int)(n % 10);
    n /= 10;

    if (a == b) {
        return false;
    }

    bool expect_a = true;

    while (n > 0) {
        int d = (int)(n % 10);
        if (expect_a) {
            if (d != a) {
                return false;
            }
        } else {
            if (d != b) {
                return false;
            }
        }
        expect_a = !expect_a;
        n /= 10;
    }

    return true;
}

int main(void)
{
    long long num;

    printf("Enter a number: ");
    if (scanf("%lld", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_undulating(num)) {
        printf("%lld is an undulating number\n", num);
    } else {
        printf("%lld is not an undulating number\n", num);
    }

    return EXIT_SUCCESS;
}