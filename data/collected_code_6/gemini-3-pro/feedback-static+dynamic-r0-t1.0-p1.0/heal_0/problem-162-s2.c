#include <stdio.h>
#include <stdlib.h>

long long calculate_sum(int n);

long long calculate_sum(int n) {
    long long sum = 0;
    
    if (n <= 0) {
        return 0;
    }
    
    while (n > 0) {
        sum += n;
        n -= 2;
    }
    
    return sum;
}

int main(void) {
    int input;
    long long result;
    
    if (scanf("%d", &input) != 1) {
        return EXIT_FAILURE;
    }
    
    result = calculate_sum(input);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}