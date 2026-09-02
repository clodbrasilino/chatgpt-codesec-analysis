#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int n) {
    int original = n, reversed = 0, remainder;
    while (n != 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    return original == reversed;
}

int find_largest_palindromic(int arr[], int size) {
    int max_palindrome = -1;
    for (int i = 0; i < size; ++i) {
        if (is_palindrome(arr[i]) && arr[i] > max_palindrome) {
            max_palindrome = arr[i];
        }
    }
    return max_palindrome;
}

int main() {
    int arr[] = {123, 121, 13431, 12321, 45654, 78987};
    int size = sizeof(arr) / sizeof(arr[0]);
    int largest_palindrome = find_largest_palindromic(arr, size);
    printf("The largest palindromic number is: %d\n", largest_palindrome);
    return 0;
}