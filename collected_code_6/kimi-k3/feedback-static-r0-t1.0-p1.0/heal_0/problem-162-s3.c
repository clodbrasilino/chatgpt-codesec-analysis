#include <stdio.h>
#include <limits.h>

int sum_alternating_series(int n) {
    int sum = 0;
    
    if (n <= 0) {
        return 0;
    }
    
    while (n > 0) {
        if (sum > INT_MAX - n) {
            return -1;
        }
        sum += n;
        n -= 2;
    }
    
    return sum;
}

int main(void) {
    int n;
    int result;
    
    printf("Enter a positive integer: ");
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    result = sum_alternating_series(n);
    
    if (result == -1) {
        fprintf(stderr, "Integer overflow occurred\n");
        return 1;
    }
    
    printf("Sum: %d\n", result);
    
    return 0;
}