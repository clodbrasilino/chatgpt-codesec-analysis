#include <stdio.h>
#include <string.h>

int min_length_by_removing_char(const char *str, char ch) {
    int count = 0;
    const char *p = str;
    while (*p) {
        if (*p == ch) {
            count++;
        }
        p++;
    }
    return p - str - count;
}

int main() {
    const char *input = "programming";
    char ch = 'm';
    int result = min_length_by_removing_char(input, ch);
    printf("Minimized length: %d\n", result);
    return 0;
}