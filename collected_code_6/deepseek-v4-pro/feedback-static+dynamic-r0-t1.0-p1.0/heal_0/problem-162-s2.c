#include <stdio.h>

int sum_positive_series(int n) {
    int sum = 0;
    int term = n;
    
    while (term > 0) {
        sum += term;
        term -= 2;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    
    int result = sum_positive_series(n);
    printf("Sum of series: %d\n", result);
    
    return 0;
}