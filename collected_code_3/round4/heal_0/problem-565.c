#include <stdio.h>
#include <string.h>

void split_string_into_chars(char *str) {
    int i, len = strlen(str);
    for(i = 0; i < len; i++) {
        printf("%c\n", str[i]);
    }
}

int main() {
    char str[] = "Hello, World!";
    split_string_into_chars(str);
    return 0;
}