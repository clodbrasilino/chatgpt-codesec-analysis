#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int num) {
    if (num < 0) {
        return false;
    }
    
    int original_num = num;
    int reversed_num = 0;
    
    while (num > 0) {
        int remainder = num % 10;
        if (reversed_num > (2147483647 - remainder) / 10) {
            return false;
        }
        reversed_num = reversed_num * 10 + remainder;
        num /= 10;
    }
    
    return original_num == reversed_num;
}

int find_largest_palindrome(const int* arr, size_t size, bool* found) {
    if (arr == NULL || found == NULL || size == 0) {
        if (found != NULL) {
            *found = false;
        }
        return -1;
    }
    
    int largest_palindrome = -1;
    *found = false;
    
    for (size_t i = 0; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if (!(*found) || arr[i] > largest_palindrome) {
                largest_palindrome = arr[i];
                *found = true;
            }
        }
    }
    
    return largest_palindrome;
}

int main(void) {
    int arr[] = {12, 121, 55, 34543, 98, 9009, -121};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    bool found = false;
    
    int largest = find_largest_palindrome(arr, size, &found);
    
    if (found) {
        printf("Largest palindromic number: %d\n", largest);
    } else {
        printf("No palindromic number found.\n");
    }
    
    return 0;
}