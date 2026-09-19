#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

bool is_palindrome(long long n) {
    if (n < 0) return false;
    long long reversed = 0, original = n;
    while (n != 0) {
        int remainder = n % 10;
        if (reversed > (LLONG_MAX - remainder) / 10) return false;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    return original == reversed;
}

long long previous_palindrome(long long n) {
    if (n == LLONG_MIN) return LLONG_MIN;
    do {
        n--;
        if (n == LLONG_MIN) break;
    } while (!is_palindrome(n));
    return n;
}

int main() {
    char buffer[20];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 1;
    long long number;
    if (scanf("%lld", &number) != 1) return 1;

    long long prev_palindrome = previous_palindrome(number);
    printf("The previous palindrome is: %lld\n", prev_palindrome);

    return 0;
}