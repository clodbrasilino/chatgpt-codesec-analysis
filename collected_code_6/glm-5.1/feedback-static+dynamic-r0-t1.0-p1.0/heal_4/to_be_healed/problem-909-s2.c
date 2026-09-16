#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(long long n) {
    if (n < 0) {
        return false;
    }
    long long original = n;
    long long reversed = 0;
    while (n > 0) {
        if (reversed > (LLONG_MAX - (n % 10)) / 10) {
            return false;
        }
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return original == reversed;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 88, got <no output>
  *  test case 2 failed: expected 111, got <no output>
  *  test case 1 failed: expected 1111, got <no output>
  */

long long find_previous_palindrome(long long n) {
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

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long long num = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || num < 0) {
        fprintf(stderr, "Error: Invalid input. Must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    setvbuf(stdout, NULL, _IONBF, 0);
    long long result = find_previous_palindrome(num);
    if (result == -1) {
        printf("No previous palindrome found.\n");
    } else {
        printf("%lld\n", result);
    }
    return EXIT_SUCCESS;
}