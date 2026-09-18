#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int reverse(int n, int digits) {
    long long rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        if (rev > INT_MAX) return -1;
        n /= 10;
    }
    if (digits % 2 == 0) {
        rev /= 10;
    }
    return rev;
}

bool isPalindrome(int n) {
    if (n < 0) return false;
    long long original = n, reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        if (reversed > INT_MAX) return false;
        n /= 10;
    }
    return original == reversed;
}

int getNextSmallestPalindrome(int n) {
    if (n < 0) return -1;
    int next = n + 1;
    while (!isPalindrome(next)) {
        next++;
    }
    return next;
}

int main() {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int result = getNextSmallestPalindrome(n);
    if (result == -1) {
        printf("No valid palindrome found\n");
    } else {
        printf("Next smallest palindrome: %d\n", result);
    }
    return 0;
}