#include <stdio.h>
#include <string.h>

char* remove_char(char *str, char ch) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != ch) {
            dst++;
        }
    }
    *dst = '\0';
    return str;
}

int main() {
    char str[] = "Hello, World!";
    char ch = 'o';

    printf("Original string: %s\n", str);
    printf("Modified string: %s\n", remove_char(str, ch));

    return 0;
}