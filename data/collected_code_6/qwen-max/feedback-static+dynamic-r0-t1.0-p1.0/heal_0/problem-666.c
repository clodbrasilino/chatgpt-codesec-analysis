#include <stdio.h>
#include <string.h>

int count_char(const char *str, char ch) {
    int count = 0;
    while (*str) {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    const char *str = "hello world";
    char ch = 'l';
    int result = count_char(str, ch);
    printf("The character '%c' appears %d times in the string.\n", ch, result);
    return 0;
}