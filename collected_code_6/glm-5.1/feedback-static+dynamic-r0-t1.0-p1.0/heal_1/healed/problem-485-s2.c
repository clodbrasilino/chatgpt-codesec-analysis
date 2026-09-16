#include <stdio.h>
#include <stdlib.h>

int is_palindrome(int num) {
    if (num < 0) {
        return 0;
    }
    int original = num;
    long reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    return original == reversed;
}

int find_largest_palindrome(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    int largest = -1;
    for (size_t i = 0; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if (arr[i] > largest) {
                largest = arr[i];
            }
        }
    }
    return largest;
}

int main(void) {
    int arr[] = {121, 123, 456, 78987, 1331, -121, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = find_largest_palindrome(arr, size);
    printf("%d\n", result);
    return 0;
}