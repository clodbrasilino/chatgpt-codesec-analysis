#include <stdio.h>
#include <string.h>

void remove_char(char *str, char c) {
    int j = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[] = "Hello, World!";
    char c = 'l';
    remove_char(str, c);
    printf("%s\n", str);
    return 0;
}