#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int num) {
    int temp = num, reverse = 0;
    while (temp != 0) {
        reverse = reverse * 10 + temp % 10;
        temp /= 10;
    }
    return num == reverse;
}

int largestPalindromicNumber(int arr[], int size) {
    int largest = 0;
    for (int i = 0; i < size; i++) {
        if (isPalindrome(arr[i]) && arr[i] > largest) {
            largest = arr[i];
        }
    }
    return largest;
}

int main() {
    int arr[] = {121, 567, 282, 12321, 45654};
    int size = sizeof(arr) / sizeof(arr[0]);
    int largest = largestPalindromicNumber(arr, size);
    printf("The largest palindromic number is %d\n", largest);
    return 0;
}