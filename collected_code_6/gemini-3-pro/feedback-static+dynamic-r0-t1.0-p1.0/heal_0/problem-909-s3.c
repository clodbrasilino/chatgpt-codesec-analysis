#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_palindrome(long long num) {
    if (num < 0) {
        return 0;
    }
    
    long long original = num;
    long long reversed = 0;
    
    while (num > 0) {
        long long digit = num % 10;
        reversed = reversed * 10 + digit;
        num /= 10;
    }
    
    return original == reversed;
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