#include <stdio.h>
#include <limits.h>

long long calculate_difference(unsigned int n) {
    if (n > 2097151U) {
        return -1;
    }

    long long sum = (long long)n * (n + 1) / 2;

    long long squared_sum = sum * sum;

    long long sum_of_squares = (long long)n * (n + 1) * (2LL * n + 1) / 6;

    if ((squared_sum > 0 && sum_of_squares < 0 && squared_sum - LLONG_MAX > sum_of_squares) ||
        (squared_sum < 0 && sum_of_squares > 0 && sum_of_squares - LLONG_MAX > squared_sum) ||
        (squared_sum >= 0 && sum_of_squares >= 0 && squared_sum > LLONG_MAX - sum_of_squares) ||
        (squared_sum <= 0 && sum_of_squares <= 0 && squared_sum < LLONG_MIN - sum_of_squares)) {
        return -1;
    }

    long long difference = squared_sum - sum_of_squares;
    return difference;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:414,execs:302,op:havoc,rep:11; likely memory-safety defect
  */

int main(void) {
    unsigned int n;

    if (scanf("%u", &n) != 1) {
        return 1;
    }

    long long result = calculate_difference(n);

    if (result == -1) {
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}