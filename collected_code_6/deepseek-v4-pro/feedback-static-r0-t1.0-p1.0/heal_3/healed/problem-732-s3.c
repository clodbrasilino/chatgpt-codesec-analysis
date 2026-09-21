#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }

    for (size_t i = 0; i < max_len - 1 && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
    str[max_len - 1] = '\0';
}

int main(void) {
    char text[100];

    if (sizeof(text) > 0) {
        strncpy(text, "Hello, world. This is a test", sizeof(text) - 1);
        text[sizeof(text) - 1] = '\0';
    }

    printf("Original: %s\n", text);
    replace_chars(text, sizeof(text));
    printf("Modified: %s\n", text);

    return 0;
}