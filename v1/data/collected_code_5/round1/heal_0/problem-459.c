#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void remove_uppercase(char *str) {
    char *src = str, *dst = str;

    while (*src) {
        if (!isupper((unsigned char)*src)) {
           *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    char str[] = "Hello WorlD!";
    printf("Before: %s\n", str);
    remove_uppercase(str);
    printf("After: %s\n", str);

    return 0;
}