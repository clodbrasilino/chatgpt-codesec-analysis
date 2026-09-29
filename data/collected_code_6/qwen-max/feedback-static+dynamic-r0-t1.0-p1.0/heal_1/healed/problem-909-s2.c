#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(long long n) {
    long long reversed = 0, original = n;
    while (n != 0) {
        int remainder = n % 10;
        reversed = reversed * 10 + remainder;
        if (reversed > LLONG_MAX / 10 || (reversed == LLONG_MAX / 10 && remainder > 7)) {
            return false;
        }
        n /= 10;
    }
    return original == reversed;
}

long long previous_palindrome(long long n) {
    do {
        n--;
    } while (!is_palindrome(n));
    return n;
}

int main() {
    long long number;
    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1) {
        return 1;
    }

    long long prev_palindrome = previous_palindrome(number);
    printf("The previous palindrome is: %lld\n", prev_palindrome);

    return 0;
}