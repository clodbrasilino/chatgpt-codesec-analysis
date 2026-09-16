#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(int num) {
    if (num < 0) return false;
    int original = num;
    int reversed = 0;
    while (num > 0) {
        int digit = num % 10;
        if (reversed > (INT_MAX - digit) / 10) return false;
        reversed = reversed * 10 + digit;
        num /= 10;
    }
    return original == reversed;
}

int largest_palindromic_number(const int *arr, int size) {
    if (arr == NULL || size <= 0) return -1;
    
    int largest = -1;
    bool found = false;
    
    for (int i = 0; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if (!found || arr[i] > largest) {
                largest = arr[i];
                found = true;
            }
        }
    }
    
    return largest;
}

int main(void) {
    int test_array[] = {121, 34, 555, 12321, 78, 989, 42, 123454321};
    int size = sizeof(test_array) / sizeof(test_array[0]);
    
    int result = largest_palindromic_number(test_array, size);
    
    if (result != -1) {
        printf("Largest palindromic number: %d\n", result);
    } else {
        printf("No palindromic number found\n");
    }
    
    int empty_array[] = {12, 34, 56, 78};
    int empty_size = sizeof(empty_array) / sizeof(empty_array[0]);
    
    int result2 = largest_palindromic_number(empty_array, empty_size);
    
    if (result2 != -1) {
        printf("Largest palindromic number: %d\n", result2);
    } else {
        printf("No palindromic number found\n");
    }
    
    int null_result = largest_palindromic_number(NULL, 5);
    if (null_result == -1) {
        printf("Invalid input handled\n");
    }
    
    return 0;
}