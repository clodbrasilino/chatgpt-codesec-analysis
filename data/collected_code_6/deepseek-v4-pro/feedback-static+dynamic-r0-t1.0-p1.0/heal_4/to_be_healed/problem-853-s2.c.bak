#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t sumOfOddFactors(int64_t n) {
    int64_t sum = 0;
    int64_t i;

    if (n == 0) {
        return 0;
    }

    if (n < 0) {
        n = -n;
    }

    for (i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            int64_t counterpart = n / i;
            if (i != counterpart && counterpart % 2 != 0) {
                sum += counterpart;
            }
        }
    }

    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:51227,execs:876,op:havoc,rep:7; likely memory-safety defect
  */

int main(void) {
    int64_t num;

    printf("Enter a number: ");
    if (scanf("%" SCNd64, &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (num == INT64_MIN) {
        printf("Sum of odd factors: %" PRId64 "\n", sumOfOddFactors(num));
        return 0;
    }

    printf("Sum of odd factors: %" PRId64 "\n", sumOfOddFactors(num));

    return 0;
}