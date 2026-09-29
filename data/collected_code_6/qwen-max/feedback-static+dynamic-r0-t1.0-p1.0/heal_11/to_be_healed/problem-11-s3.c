#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_char_occurrences(char *str, char ch, size_t max_len) {
    if (str == NULL || max_len == 0) return;

    char *src = str;
    char *dst = str;

    while (*src && (size_t)(src - str) < max_len) {
        if (*src != ch) {
            if ((size_t)(dst - str) < max_len - 1) {
                *dst = *src;
                dst++;
            }
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100] = "hello world";
    char ch = 'l';

    printf("Original string: %s\n", str);
    remove_char_occurrences(str, ch, sizeof(str));
    printf("Modified string: %s\n", str);

    return 0;
}