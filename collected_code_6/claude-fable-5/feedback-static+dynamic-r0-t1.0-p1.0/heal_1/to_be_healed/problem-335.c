#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int ap_sum(long long a, long long d, long long n, long long *result)
{
    long long last;
    long long total;

    if (result == NULL || n <= 0) {
        return -1;
    }

    if (d != 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000003,sig:06,src:000013,time:11613,execs:6697,op:havoc,rep:1)
         */
        if ((n - 1) > 0 && (d > 0 ? d : -d) > LLONG_MAX / (n - 1)) {
            return -1;
        }
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 * 5 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000013,time:11613,execs:6697,op:havoc,rep:1)
     */
    last = d * (n - 1);

    if ((last > 0 && a > LLONG_MAX - last) ||
        (last < 0 && a < LLONG_MIN - last)) {
        return -1;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 + 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000006,time:1861,execs:912,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:1959,execs:971,op:havoc,rep:1)
     */
    total = 2 * a + last;

    if (a > LLONG_MAX / 2 || a < LLONG_MIN / 2) {
        return -1;
    }

    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000006,time:1861,execs:912,op:havoc,rep:1)
     */
    if (total != 0 && n > LLONG_MAX / (total > 0 ? total : -total)) {
        return -1;
    }

    total = total * n;

    *result = total / 2;

    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000012,time:11412,execs:6574,op:havoc,rep:2; likely memory-safety defect
  */

int main(void)
{
    long long a;
    long long d;
    long long n;
    long long sum;

    printf("Enter first term: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for first term\n");
        return EXIT_FAILURE;
    }

    printf("Enter common difference: ");
    if (scanf("%lld", &d) != 1) {
        fprintf(stderr, "Invalid input for common difference\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of terms: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for number of terms\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Number of terms must be positive\n");
        return EXIT_FAILURE;
    }

    if (ap_sum(a, d, n, &sum) != 0) {
        fprintf(stderr, "Computation failed due to invalid input or overflow\n");
        return EXIT_FAILURE;
    }

    printf("Sum of arithmetic progression: %lld\n", sum);

    return EXIT_SUCCESS;
}