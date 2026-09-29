#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_sum_of_squares(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        sum += (unsigned long long)i * i;
    }
    
    return sum;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = calculate_sum_of_squares(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}