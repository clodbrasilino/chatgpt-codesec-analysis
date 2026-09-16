#include <stdio.h>
#include <limits.h>

static int is_palindrome(int num) {
    if (num < 0) {
        return 0;
    }
    
    if (num < 10) {
        return 1;
    }
    
    int original = num;
    int reversed = 0;
    
    while (num > 0) {
        int digit = num % 10;
        
        if (reversed > (INT_MAX - digit) / 10) {
            return 0;
        }
        
        reversed = reversed * 10 + digit;
        num /= 10;
    }
    
    return original == reversed;
}

int find_largest_palindrome(const int arr[], size_t size, int *result) {
    if (arr == NULL || result == NULL) {
        return -1;
    }
    
    if (size == 0) {
        return -2;
    }
    
    int largest = INT_MIN;
    int found = 0;
    
    for (size_t i = 0; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if (!found || arr[i] > largest) {
                largest = arr[i];
                found = 1;
            }
        }
    }
    
    if (!found) {
        return -3;
    }
    
    *result = largest;
    return 0;
}

int main(void) {
    int arr[] = {121, 232, 545, 999, 123, 454};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;
    
    int status = find_largest_palindrome(arr, size, &result);
    
    if (status == 0) {
        printf("Largest palindromic number: %d\n", result);
    } else if (status == -1) {
        fprintf(stderr, "Error: Invalid pointer argument\n");
        return 1;
    } else if (status == -2) {
        fprintf(stderr, "Error: Empty array\n");
        return 1;
    } else if (status == -3) {
        fprintf(stderr, "Error: No palindromic number found\n");
        return 1;
    }
    
    return 0;
}