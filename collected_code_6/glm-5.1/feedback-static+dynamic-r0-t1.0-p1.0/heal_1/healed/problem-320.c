#include <stdio.h>
#include <limits.h>

long long calculate_difference(unsigned int n) {
    long long sum = (long long)n * (n + 1) / 2;
    
    if (sum > 3037000499LL || sum < -3037000500LL) {
        return -1;
    }
    
    long long squared_sum = sum * sum;
    
    if (n > 2097151U) {
        return -1;
    }
    
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