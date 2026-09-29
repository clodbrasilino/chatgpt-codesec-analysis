#include <stdio.h>
#include <string.h>

char* remove_spaces(char *str) {
    char *src = str;
    char *dst = str;
    while (*src) {
        if (*src != ' ') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return str;
}

int main() {
    char str[] = " A string  with   spaces ";
    printf("Original: '%s'\n", str);
    char *result = remove_spaces(str);
    printf("Modified: '%s'\n", result);
    return 0;
}