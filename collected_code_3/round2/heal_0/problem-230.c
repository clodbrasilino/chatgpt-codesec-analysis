#include <stdio.h>
#include <string.h>

void replace_blank_with_char(char *str, char ch) {
    int i;
    for(i = 0; str[i]; i++) {
        if(str[i] == ' ') {
            str[i] = ch;
        }
    }
}

int main() {
    char str[] = "Hello World!";
    char ch = '*';

    printf("Original string: %s\n", str);
    replace_blank_with_char(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}