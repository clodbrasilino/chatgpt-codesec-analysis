#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int n) {
    int reversed = 0;
    int original = n;
    while (n != 0) {
        int digit = n % 10;
        reversed = reversed * 10 + digit;
        n /= 10;
    }
    return original == reversed;
}

int largestPalindrome(int arr[], int n) {
    int max = -1;
    for (int i = 0; i < n; i++) {
        if (isPalindrome(arr[i]) && arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int arr[] = {123, 121, 131, 132, 232, 111, 222, 333, 444, 555};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = largestPalindrome(arr, n);
    if (max == -1) {
        printf("No palindrome found\n");
    } else {
        printf("Largest palindrome is %d\n", max);
    }
    return 0;
}