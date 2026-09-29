#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str, size_t len) {
    int i, j = 0;
    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char strings[] = {"123abc456", "789def012", "345ghi678"};
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    for (int i = 0; i < num_strings; i++) {
        size_t str_len = strlen(strings[i]);
        remove_digits(strings[i], str_len);
        printf("%s\n", strings[i]);
    }

    return 0;
}