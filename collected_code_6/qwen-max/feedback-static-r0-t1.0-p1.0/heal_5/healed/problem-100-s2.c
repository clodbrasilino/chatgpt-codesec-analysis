#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

bool is_palindrome(long num) {
    char str[25];
    int ret = snprintf(str, sizeof(str), "%ld", num);
    if (ret < 0 || ret >= sizeof(str)) {
        return false;
    }
    str[sizeof(str) - 1] = '\0';
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