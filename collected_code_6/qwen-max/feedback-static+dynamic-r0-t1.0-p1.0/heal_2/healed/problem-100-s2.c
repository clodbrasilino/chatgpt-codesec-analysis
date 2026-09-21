#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

bool is_palindrome(long num) {
    char str[25];
    snprintf(str, sizeof(str), "%ld", num);
    size_t len = strlen(str);
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
    printf("%ld\n", next_palindrome(num));
    return 0;
}