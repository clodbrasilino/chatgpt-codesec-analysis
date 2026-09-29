#include <stdio.h>
#include <stdlib.h>

long long calculate_sum(int n);

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    long long sum = calculate_sum(n);
    printf("%lld\n", sum);
    
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