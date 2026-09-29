#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str) {
    if (str == NULL) return;
    char *src = str, *dst = str;
    while (*src != '\0') {
        if (!isdigit((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    char strings[][16] = {"123abc456", "789def012", "345ghi678"};
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    for (int i = 0; i < num_strings; i++) {
        remove_digits(strings[i]);
        printf("%s\n", strings[i]);
    }

    return 0;
}