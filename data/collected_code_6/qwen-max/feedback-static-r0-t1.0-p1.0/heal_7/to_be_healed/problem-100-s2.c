#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

bool is_palindrome(long num) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[25];
    snprintf(str, sizeof(str), "%ld", num);
    size_t len = strnlen(str, sizeof(str));
    for (size_t i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

long next_palindrome(long num) {
    while (1) {
        ++num;
        if (is_palindrome(num)) {
            return num;
        }
    }
}

int main() {
    long num = 12345;
    printf("%" PRIdMAX "\n", (intmax_t)next_palindrome(num));
    return 0;
}