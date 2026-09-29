#include <stdio.h>
#include <string.h>

void remove_even_chars(char *str) {
    int len = 0;
    while (str[len] != '\0') len++;

    for (int i = 0; i < len; ) {
        if ((i % 2) == 0 && i != 0) {
            memmove(&str[i], &str[i + 1], len - i);
            len--;
        } else {
            i++;
        }
    }
    str[len] = '\0';
}

int main() {
    char str[] = "abcdefghijklmnopqrstuvwxyz";
    printf("Original String: %s\n", str);
    remove_even_chars(str);
    printf("Modified String: %s\n", str);
    return 0;
}