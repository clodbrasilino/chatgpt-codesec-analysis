#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_abundant(int num) {
    if (num <= 0) {
        return false;
    }
    
    int sum = 0;
    int i;
    
    for (i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            if (sum > INT_MAX - i) {
                return true;
            }
            sum += i;
        }
    }
    
    return sum > num;
}

int main(void) {
    int num;
    int result;
    
    printf("Enter a positive integer: ");
    result = scanf("%d", &num);
    
    if (result != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    if (num <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    
    if (is_abundant(num)) {
        printf("%d is an abundant number.\n", num);
    } else {
        printf("%d is not an abundant number.\n", num);
    }
    
    return 0;
}