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
    int ret = snprintf(str, sizeof(str), "%ld", num);
    if (ret < 0 || ret >= sizeof(str)) {
        return false;
    }
    str[sizeof(str) - 1] = '\0'; // Ensure the string is null-terminated
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
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