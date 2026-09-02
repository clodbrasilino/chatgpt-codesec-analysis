#include <stdio.h>

int sum_positive_series(int n) {
    int sum = 0;
    
    if (n <= 0) {
        return 0;
    }
    
    for (int i = n; i > 0; i -= 2) {
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
    printf("Sum: %d\n", result);
    
    return 0;
}