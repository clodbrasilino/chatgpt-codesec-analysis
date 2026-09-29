#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

bool is_palindrome(long num) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[25];
    snprintf(str, sizeof(str), "%ld", num);
    for (size_t i = 0; i < 24; ++i) {
        if (str[i] == '\0') {
            size_t len = i;
            for (size_t j = 0; j < len / 2; ++j) {
                if (str[j] != str[len - 1 - j]) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
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
    printf("%ld\n", next_palindrome(num));
    return 0;
}