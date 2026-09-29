#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_fourth_power_odd(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        int64_t odd = 2LL * i - 1;
        int64_t square = odd * odd;
        sum += square * square;
    }
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 0) {
        return 1;
    }
    
    printf("%" PRId64 "\n", sum_fourth_power_odd(n));
    
    return 0;
}