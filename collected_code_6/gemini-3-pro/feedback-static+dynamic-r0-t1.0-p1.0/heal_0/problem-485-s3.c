#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int n) {
    if (n < 0) {
        return false;
    }
    
    int reversed = 0;
    int original = n;
    
    while (n > 0) {
        int digit = n % 10;
        if (reversed > (2147483647 - digit) / 10) {
            return false;
        }
        reversed = reversed * 10 + digit;
        n /= 10;
    }
    
    return original == reversed;
}

int find_largest_palindrome(const int* arr, size_t size, bool* found) {
    if (arr == NULL || found == NULL) {
        if (found != NULL) {
            *found = false;
        }
        return -1;
    }

    int largest = -1;
    *found = false;

    for (size_t i = 0; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if (!*found || arr[i] > largest) {
                largest = arr[i];
                *found = true;
            }
        }
    }

    return largest;
}

int main(void) {
    int arr[] = {123, 454, 99, 12321, 878, 10001, -121};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    bool found;

    int largest = find_largest_palindrome(arr, size, &found);

    if (found) {
        printf("%d\n", largest);
    } else {
        printf("No palindromic number found.\n");
    }

    return 0;
}