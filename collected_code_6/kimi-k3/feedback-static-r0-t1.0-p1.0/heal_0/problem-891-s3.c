#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int countDigits(long long num) {
    int count = 0;
    if (num == 0) {
        return 1;
    }
    if (num < 0) {
        if (num == LLONG_MIN) {
            num = LLONG_MAX;
        } else {
            num = -num;
        }
    }
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

int haveSameDigits(long long num1, long long num2) {
    return countDigits(num1) == countDigits(num2);
}

int main(void) {
    long long num1 = 0;
    long long num2 = 0;
    int result = 0;
    
    printf("Enter two numbers: ");
    result = scanf("%lld %lld", &num1, &num2);
    
    if (result != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (haveSameDigits(num1, num2)) {
        printf("Both numbers have the same number of digits.\n");
    } else {
        printf("Numbers have different number of digits.\n");
    }
    
    return EXIT_SUCCESS;
}