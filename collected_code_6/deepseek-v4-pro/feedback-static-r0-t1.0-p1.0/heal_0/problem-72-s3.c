#include <stdio.h>

int can_be_difference_of_squares(long long n) {
    if (n < 0) {
        return 0;
    }
    if (n % 4 == 2) {
        return 0;
    }
    return 1;
}

int main(void) {
    long long num;
    
    printf("Enter a number: ");
    if (scanf("%lld", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    if (can_be_difference_of_squares(num)) {
        printf("%lld can be represented as difference of two squares.\n", num);
    } else {
        printf("%lld cannot be represented as difference of two squares.\n", num);
    }
    
    return 0;
}