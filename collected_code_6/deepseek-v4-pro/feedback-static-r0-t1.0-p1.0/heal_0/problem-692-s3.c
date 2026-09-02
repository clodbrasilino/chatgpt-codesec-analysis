#include <stdio.h>

int last_two_digits_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    
    if (n >= 10) {
        return 0;
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % 100;
    }
    
    return result;
}

int main(void) {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = last_two_digits_factorial(n);
    if (result < 0) {
        printf("Factorial is not defined for negative numbers\n");
        return 1;
    }
    
    printf("Last two digits of %d!: %02d\n", n, result);
    
    return 0;
}