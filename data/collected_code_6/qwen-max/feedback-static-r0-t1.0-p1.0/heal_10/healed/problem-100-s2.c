#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>
#include <errno.h>

bool is_palindrome(long num) {
    char str[25];
    int ret = snprintf(str, sizeof(str), "%ld", num);
    if (ret < 0 || (size_t)ret >= sizeof(str)) {
        return false;
    }
    for (size_t i = 0; i < strlen(str) / 2; ++i) {
        if (str[i] != str[strlen(str) - 1 - i]) {
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