#include <stdio.h>
#include <string.h>

void replace_spaces_with_char(char *str, char replacement) {
    if (str == NULL) return;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main() {
    char input[100] = "This is a test string";
    char replacement = '*';
    replace_spaces_with_char(input, replacement);
    printf("%s\n", input);
    return 0;
}