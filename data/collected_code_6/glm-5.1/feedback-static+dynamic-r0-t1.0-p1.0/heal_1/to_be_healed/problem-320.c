#include <stdio.h>
#include <limits.h>

long long calculate_difference(unsigned int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3736928712 * 3736928713 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:2915,execs:1771,op:havoc,rep:1)
     */
    long long sum = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 98765456790 * 98765456790 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:895,execs:578,op:havoc,rep:8)
     * UBSan: signed integer overflow: -2241053935701321980 * -2241053935701321980 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:2915,execs:1771,op:havoc,rep:1)
     */
    long long squared_sum = sum * sum;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4482107871402643960 * 7473857425 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:2915,execs:1771,op:havoc,rep:1)
     * UBSan: signed integer overflow: 3736928712 * 3736928713 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:2915,execs:1771,op:havoc,rep:1)
     */
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