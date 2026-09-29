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
    }
    return -1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
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