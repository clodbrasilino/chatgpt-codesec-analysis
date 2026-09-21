#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_char_occurrences(char *str, char ch) {
    if (str == NULL) return;

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            memmove(&str[i], &str[i + 1], len - i);
            str[len - 1] = '\0';
            len--;
            i--;
        }
    }
}

int main() {
    char str[] = "hello world";
    char ch = 'l';

    printf("Original string: %s\n", str);
    remove_char_occurrences(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}