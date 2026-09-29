#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 2
  */

static unsigned long long min_operations(long long a, long long b)
{
    unsigned long long count;

    if (a >= b) {
        return (unsigned long long)(a - b);
    }

    count = 0;
    while (b > a) {
        if (b % 2 == 0) {
            b /= 2;
        } else {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:2464,execs:1967,op:havoc,rep:1)
             */
            b += 1;
        }
        count++;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:2464,execs:1967,op:havoc,rep:1)
     */
    return count + (unsigned long long)(a - b);
}

int main(void)
{
    long long a;
    long long b;
    int result;

    printf("Enter first number: ");
    result = scanf("%lld", &a);
    if (result != 1) {
        fprintf(stderr, "Invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    result = scanf("%lld", &b);
    if (result != 1) {
        fprintf(stderr, "Invalid input for second number\n");
        return EXIT_FAILURE;
    }

    if (a <= 0 || b <= 0) {
        fprintf(stderr, "Inputs must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Minimum operations required: %llu\n", min_operations(a, b));

    return EXIT_SUCCESS;
}