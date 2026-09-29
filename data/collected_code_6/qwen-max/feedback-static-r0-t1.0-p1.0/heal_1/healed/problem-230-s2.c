#include <stdio.h>
#include <string.h>

void replace_spaces_with_char(char *str, size_t len, char replacement) {
    if (str == NULL || len == 0) return;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main() {
    char input[100] = "This is a test string";
    char replacement = '*';
    replace_spaces_with_char(input, sizeof(input), replacement);
    printf("%s\n", input);
    return 0;
}