#include <stdio.h>
#include <stdlib.h>

static int is_perfect_square(long long num)
{
    long long low;
    long long high;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    long long mid;
    /* Possible weaknesses found:
     *  The scope of the variable 'sq' can be reduced. [variableScope]
     */
    long long sq;

    if (num < 0) {
        return 0;
    }
    if (num < 2) {
        return 1;
    }

    low = 1;
    high = num / 2;

    while (low <= high) {
        mid = low + (high - low) / 2;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 833333333333334 * 833333333333334 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:440,execs:288,op:havoc,rep:1)
         */
        sq = mid * mid;
        if (sq == num) {
            return 1;
        } else if (sq < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

int main(void)
{
    long long num;

    printf("Enter a number: ");
    if (scanf("%lld", &num) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (num > 3037000499LL * 3037000499LL) {
        fprintf(stderr, "Number too large.\n");
        return EXIT_FAILURE;
    }

    if (is_perfect_square(num)) {
        printf("%lld is a perfect square.\n", num);
    } else {
        printf("%lld is not a perfect square.\n", num);
    }

    return EXIT_SUCCESS;
}