#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static long long integer_sqrt(long long n)
{
    if (n <= 0) {
        return n < 0 ? -1 : 0;
    }

    long long root = (long long)sqrt((double)n);

    while (root > 0 && root * root > n) {
        root--;
    }
    while ((root + 1) * (root + 1) <= n) {
        root++;
    }

    return root;
}

static bool is_sum_of_two_squares(long long n)
{
    for (long long a = 0; a * a <= n; a++) {
        long long remainder = n - a * a;
        long long b = integer_sqrt(remainder);

        if (b * b == remainder) {
            return true;
        }
    }

    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:798,execs:296,op:havoc,rep:2; likely memory-safety defect
  */

int main(void)
{
    long long number;

    printf("Enter a non-negative integer: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (number < 0) {
        fprintf(stderr, "Error: number must be non-negative.\n");
        return 1;
    }

    if (is_sum_of_two_squares(number)) {
        printf("%lld can be represented as the sum of two squares.\n", number);
    } else {
        printf("%lld cannot be represented as the sum of two squares.\n", number);
    }

    return 0;
}