#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t sum_of_fifth_power_odd(int n) {
    uint64_t sum = 0;
    uint64_t odd_num = 1;
    
    for (int i = 0; i < n; i++) {
        uint64_t odd_squared = odd_num * odd_num;
        uint64_t odd_fourth = odd_squared * odd_squared;
        sum += odd_fourth * odd_num;
        odd_num += 2;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("n must be non-negative\n");
        return 1;
    }
    
    printf("Sum of fifth powers of first %d odd natural numbers: %" PRIu64 "\n", 
           n, sum_of_fifth_power_odd(n));
    
    return 0;
}