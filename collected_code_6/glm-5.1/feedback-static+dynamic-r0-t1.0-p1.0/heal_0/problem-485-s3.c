#include <stdio.h>
#include <stdlib.h>

int is_palindrome(int num) {
    if (num < 0) {
        return 0;
    }
    long long reversed = 0;
    long long original = num;
    while (original > 0) {
        reversed = reversed * 10 + original % 10;
        original /= 10;
    }
    return reversed == num;
}

int find_largest_palindrome(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    int largest = -1;
    for (size_t i = 0; i < size; i++) {
        if (is_palindrome(arr[i]) && arr[i] > largest) {
            largest = arr[i];
        }
    }
    return largest;
}

int main(void) {
    int arr[] = {121, 545, 999, 12321, -121, 123, 88};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = find_largest_palindrome(arr, size);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("-1\n");
    }
    return 0;
}