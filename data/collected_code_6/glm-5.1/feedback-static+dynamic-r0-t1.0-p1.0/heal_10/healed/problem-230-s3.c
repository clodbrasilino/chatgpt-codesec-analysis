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
    snprintf(buffer, sizeof(buffer), "%s", input);
    printf("Original: %s\n", buffer);
    replace_spaces(buffer, '-', sizeof(buffer) - 1);
    printf("Modified: %s\n", buffer);
    return 0;
}