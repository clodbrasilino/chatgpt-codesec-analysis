#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_common_divisors(long long a, long long b)
{
    if (a == 0 && b == 0) {
        return 0;
    }

    if (a == LLONG_MIN || b == LLONG_MIN) {
        return 0;
    }

    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }

    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }

    long long gcd = a;
    long long sum = 0;

    for (long long i = 1; i <= gcd / i; i++) {
        if (gcd % i == 0) {
            sum += i;
            if (i != gcd / i) {
                sum += gcd / i;
            }
        }
    }

    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:578,execs:575,op:havoc,rep:3; likely memory-safety defect
  */

int main(void)
{
    long long num1, num2;

    if (scanf("%lld %lld", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }

    long long result = sum_common_divisors(num1, num2);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}