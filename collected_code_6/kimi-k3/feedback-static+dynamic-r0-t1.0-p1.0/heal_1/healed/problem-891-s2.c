#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int countDigits(long long num) {
    int count = 0;
    uint64_t u;
    
    if (num == 0) {
        return 1;
    }
    
    if (num < 0) {
        u = (uint64_t)(-(num + 1)) + 1;
    } else {
        u = (uint64_t)num;
    }
    
    while (u > 0) {
        u /= 10;
        count++;
    }
    
    return count;
}

int hasSameDigits(long long num1, long long num2) {
    return countDigits(num1) == countDigits(num2);
}

int main(void) {
    long long num1, num2;
    
    if (scanf("%lld %lld", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    if (hasSameDigits(num1, num2)) {
        printf("Same number of digits\n");
    } else {
        printf("Different number of digits\n");
    }
    
    return EXIT_SUCCESS;
}