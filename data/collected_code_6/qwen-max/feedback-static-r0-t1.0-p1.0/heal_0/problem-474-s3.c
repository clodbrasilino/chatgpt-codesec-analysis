#include <stdio.h>
#include <string.h>

void replace_char(char *str, char old_char, char new_char) {
    if (str == NULL) return;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == old_char) {
            str[i] = new_char;
        }
    }
}

int main() {
    char str[] = "Hello, World!";
    char old_char = 'o';
    char new_char = 'a';

    replace_char(str, old_char, new_char);

    printf("Modified string: %s\n", str);

    return 0;
}