#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

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
    }
    return -1;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (argv[1] == NULL) {
        return EXIT_FAILURE;
    }
    size_t len = 0;
    while (argv[1][len] != '\0') {
        len++;
    }
    if (len == 0 || len > 19) {
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long long num = strtoll(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || endptr == argv[1]) {
        return EXIT_FAILURE;
    }
    long long result = previous_palindrome(num);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}