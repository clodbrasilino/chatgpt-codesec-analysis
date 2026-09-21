#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_char_occurrences(char *str, char ch) {
    if (str == NULL) return;
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*src != ch) {
            dst++;
        }
    }
    *dst = '\0';
}

int main() {
    char str[] = "hello world";
    char ch = 'l';

    printf("Original string: %s\n", str);
    remove_char_occurrences(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}