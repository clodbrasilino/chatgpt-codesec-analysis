#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_chars(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }

    int count = 0;
    while (*str != '\0' && count < n) {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
            count++;
        }
        str++;
    }
}

int main() {
    char test_str[] = "Hello, world. This is a test string.";
    int n = 5;

    printf("Original: %s\n", test_str);
    replace_chars(test_str, n);
    printf("Modified: %s\n", test_str);

    return 0;
}