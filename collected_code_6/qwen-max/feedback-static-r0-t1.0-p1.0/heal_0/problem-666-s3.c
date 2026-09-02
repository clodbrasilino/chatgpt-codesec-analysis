#include <stdio.h>
#include <string.h>

int count_char(const char *str, char c) {
    int count = 0;
    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    const char *test_str = "hello world";
    char target = 'l';
    int result = count_char(test_str, target);
    printf("The character '%c' appears %d times in the string.\n", target, result);
    return 0;
}