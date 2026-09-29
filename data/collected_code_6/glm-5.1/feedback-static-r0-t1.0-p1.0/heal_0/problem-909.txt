#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_palindrome(long long n) {
    if (n < 0) {
        return false;
    }
    long long original = n;
    long long reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return original == reversed;
}

long long previous_palindrome(long long n) {
    if (n <= 0) {
        return -1;
    }
    long long current = n - 1;
    while (current >= 0) {
        if (is_palindrome(current)) {
            return current;
        }
        current--;
        if (current < 0) {
            break;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long long num = atoll(argv[1]);
    long long result = previous_palindrome(num);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}