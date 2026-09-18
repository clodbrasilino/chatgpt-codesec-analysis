#include <stdio.h>

int last_digit_factorial(int num) {
    if(num < 0) {
        return -1;
    }
    if(num == 0 || num == 1) {
        return 1;
    }
    else {
        int last_digit = 1, i;
        for(i=2; i<=num; i++) {
            last_digit = (last_digit * i) % 10;
        }
        return last_digit;
    }
}

int main() {
    int a, b, last_digit_a, last_digit_b;
    
    printf("Enter the number a: ");
    scanf("%d", &a);
    printf("Enter the number b: ");
    scanf("%d", &b);
    
    last_digit_a = last_digit_factorial(a);
    last_digit_b = last_digit_factorial(b);
    
    if(last_digit_a == -1 || last_digit_b == -1) {
        printf("Error! Factorial of negative number doesn't exist.\n");
        return -1;
    }
    
    if(last_digit_a % last_digit_b == 0) {
        printf("The factorial of a divides the factorial of b \n");
    }
    else {
        printf("The factorial of a does not divide the factorial of b \n");
    }
    
    return 0;
}