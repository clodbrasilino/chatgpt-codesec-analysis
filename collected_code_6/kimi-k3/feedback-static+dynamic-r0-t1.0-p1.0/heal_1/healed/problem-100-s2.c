#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(unsigned long long num) {
    unsigned long long original = num;
    unsigned long long reversed = 0;
    
    while (num > 0) {
        if (reversed > (18446744073709551615ULL - (num % 10)) / 10) {
            return false;
        }
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    
    return original == reversed;
}

unsigned long long next_smallest_palindrome(unsigned long long num) {
    if (num == 18446744073709551615ULL) {
        return 0;
    }
    
    unsigned long long candidate = num + 1;
    
    while (candidate != 0) {
        if (is_palindrome(candidate)) {
            return candidate;
        }
        candidate++;
    }
    
    return 0;
}

int main(void) {
    unsigned long long num;
    
    if (scanf("%llu", &num) != 1) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = next_smallest_palindrome(num);
    
    if (result == 0) {
        printf("0\n");
    } else {
        printf("%llu\n", result);
    }
    
    return EXIT_SUCCESS;
}