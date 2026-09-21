#include <stdio.h>
#include <stdlib.h>

int is_palindrome(long long num) {
    if (num < 0) {
        return 0;
    }
    
    long long temp = num;
    long long reversed = 0;
    
    while (temp > 0) {
        long long digit = temp % 10;
        
        if (reversed > (9223372036854775807LL - digit) / 10) {
            return 0;
        }
        
        reversed = reversed * 10 + digit;
        temp /= 10;
    }
    
    return num == reversed;
}

long long get_previous_palindrome(long long num) {
    if (num <= 0) {
        return -1;
    }
    
    long long current = num - 1;
    
    while (current >= 0) {
        if (is_palindrome(current)) {
            return current;
        }
        current--;
    }
    
    return -1;
}

int main(void) {
    long long input = 0;
    
    if (scanf("%lld", &input) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = get_previous_palindrome(input);
    
    if (result == -1) {
        fprintf(stderr, "No previous palindrome found\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}