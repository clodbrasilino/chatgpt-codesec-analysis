#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char c, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }
    size_t str_len = strnlen(str, len);
    for (size_t i = 0; i < str_len; i++) {
        if (str[i] == ' ') {
            str[i] = c;
        }
    }
}

int main(int argc, char *argv[]) {
    char buffer[256];
    const char *input = "Replace blank spaces with any character";
    size_t input_len = strlen(input);
    size_t copy_len = (input_len < sizeof(buffer)) ? input_len : sizeof(buffer) - 1;
    memcpy(buffer, input, copy_len);
    buffer[copy_len] = '\0';
    printf("Original: %s\n", buffer);
    replace_spaces(buffer, '-', sizeof(buffer));
    printf("Modified: %s\n", buffer);
    return 0;
}