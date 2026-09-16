#include <stdio.h>
#include <stdlib.h>

long long calculate_sum(int n);

int main(void) {
    int input;
    
    if (scanf("%d", &input) != 1) {
        return EXIT_FAILURE;
    }
    
    if (input < 0) {
        return EXIT_FAILURE;
    }
    
    long long result = calculate_sum(input);
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}

long long calculate_sum(int n) {
    long long sum = 0;
    
    while (n > 0) {
        sum += n;
        n -= 2;
    }
    
    return sum;
}