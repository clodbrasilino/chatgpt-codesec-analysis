#include <stdio.h>
#include <string.h>

char* remove_spaces(char *str) {
    char *dst = str;
    while (*str) {
        if (*str != ' ') {
            *dst++ = *str;
        }
        str++;
    }
    *dst = '\0';
    return dst;
}

int main() {
    char str[] = " A string  with   spaces ";
    printf("Original: '%s'\n", str);
    remove_spaces(str);
    printf("Modified: '%s'\n", str);
    return 0;
}