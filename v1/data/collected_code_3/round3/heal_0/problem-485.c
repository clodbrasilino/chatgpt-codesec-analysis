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
    int maxPalindrome = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxPalindrome && isPalindrome(arr[i])) {
            maxPalindrome = arr[i];
        }
    }
    return maxPalindrome;
}

int main() {
    int arr[] = {123, 121, 131, 132, 232, 345, 454, 555, 666, 789};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxPalindrome = largestPalindrome(arr, n);
    if (maxPalindrome == -1) {
        printf("No palindromic number found in the array.\n");
    } else {
        printf("The largest palindromic number is %d.\n", maxPalindrome);
    }
    return 0;
}