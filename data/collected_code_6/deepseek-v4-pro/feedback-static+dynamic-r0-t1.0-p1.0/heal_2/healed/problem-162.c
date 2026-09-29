#include <stdio.h>
#include <limits.h>

int sum_positive_series(int n) {
    int sum = 0;
    
    if (n <= 0) {
        return 0;
    }
    
    for (int i = n; i > 0; i -= 2) {
        if (i > 0 && sum > INT_MAX - i) {
            return -1;
        }
        sum += i;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = sum_positive_series(n);
    if (result == -1 && n > 0) {
        printf("Overflow detected\n");
        return 1;
    }
    
    printf("Sum: %d\n", result);
    
    return 0;
}