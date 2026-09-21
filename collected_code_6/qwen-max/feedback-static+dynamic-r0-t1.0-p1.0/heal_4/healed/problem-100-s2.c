#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

bool is_palindrome(long num) {
    char *str = malloc(25 * sizeof(char));
    if (str == NULL) {
        return false;
    }
    snprintf(str, 25, "%ld", num);
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - 1 - i]) {
            free(str);
            return false;
        }
    }
    free(str);
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