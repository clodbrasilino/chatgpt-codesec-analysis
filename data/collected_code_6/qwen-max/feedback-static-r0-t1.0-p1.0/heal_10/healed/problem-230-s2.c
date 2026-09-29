#include <stdio.h>
#include <string.h>

void replace_spaces_with_char(char *str, size_t max_len, char replacement) {
    if (str == NULL || max_len == 0) return;
    for (size_t i = 0; i < max_len - 1 && str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main() {
    char input[100] = "This is a test string";
    size_t input_len = strnlen(input, sizeof(input) - 1);
    if (input[input_len] != '\0') {
        input[sizeof(input) - 1] = '\0';
    }
    replace_spaces_with_char(input, sizeof(input), '*');
    printf("%s\n", input);
    return 0;
}