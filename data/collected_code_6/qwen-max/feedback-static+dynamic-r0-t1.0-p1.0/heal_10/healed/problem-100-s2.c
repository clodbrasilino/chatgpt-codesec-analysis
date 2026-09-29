#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

bool is_palindrome(long num) {
    char str[26];
    int len = snprintf(str, sizeof(str), "%ld", num);
    if (len >= 25) {
        return false;
    }
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
    printf("%ld\n", next_palindrome(num));
    return 0;
}