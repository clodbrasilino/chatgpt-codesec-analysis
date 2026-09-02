#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int last_digit_of_factorial_division(int a, int b) {
    if (a < 0 || b < 0 || a > b) {
        return -1;
    }
    
    if (a == b) {
        return 1;
    }
    
    if (b == 0) {
        return 1;
    }
    
    if (b >= 5) {
        return 0;
    }
    
    int result = 1;
    for (int i = a + 1; i <= b; i++) {
        result = (result * i) % 10;
    }
    
    return result;
}

int main(void) {
    int a, b;
    
    printf("Enter a: ");
    if (scanf("%d", &a) != 1) {
        return 1;
    }
    
    printf("Enter b: ");
    if (scanf("%d", &b) != 1) {
        return 1;
    }
    
    int result = last_digit_of_factorial_division(a, b);
    
    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}