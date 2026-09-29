#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int find_digit_difference(long long num) {
    unsigned long long n;
    if (num < 0) {
        n = -(unsigned long long)num;
    } else {
        n = (unsigned long long)num;
    }
    
    int even_sum = 0;
    int odd_sum = 0;
    
    while (n > 0) {
        int digit = n % 10;
        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        n /= 10;
    }
    
    return even_sum - odd_sum;
}

int main() {
    long long num;
    
    if (scanf("%lld", &num) != 1) {
        return EXIT_FAILURE;
    }
    
    int difference = find_digit_difference(num);
    
    printf("%d\n", difference);
    
    return EXIT_SUCCESS;
}