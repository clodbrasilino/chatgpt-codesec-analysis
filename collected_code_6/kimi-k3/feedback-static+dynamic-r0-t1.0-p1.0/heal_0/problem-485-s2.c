#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static bool is_palindrome(long long num) {
    if (num < 0) {
        return false;
    }
    
    if (num < 10) {
        return true;
    }
    
    long long original = num;
    long long reversed = 0;
    
    while (num > 0) {
        int digit = num % 10;
        if (reversed > (LLONG_MAX - digit) / 10) {
            return false;
        }
        reversed = reversed * 10 + digit;
        num /= 10;
    }
    
    return original == reversed;
}

static int find_largest_palindrome(const long long arr[], size_t size, long long *result) {
    if (arr == NULL || result == NULL || size == 0) {
        return -1;
    }
    
    long long largest = LLONG_MIN;
    bool found = false;
    
    for (size_t i = 0; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if (!found || arr[i] > largest) {
                largest = arr[i];
                found = true;
            }
        }
    }
    
    if (!found) {
        return -1;
    }
    
    *result = largest;
    return 0;
}

int main(void) {
    long long arr[] = {121, 232, 5454, 123, 99999, 12321};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    long long result;
    
    if (find_largest_palindrome(arr, size, &result) == 0) {
        printf("Largest palindromic number: %lld\n", result);
    } else {
        printf("No palindromic number found\n");
    }
    
    return 0;
}