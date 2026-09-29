#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_valid_string(const char *str, size_t max_len) {
    return strnlen(str, max_len) < max_len;
}

void capitalize_first_last(char *str, size_t max_len) {
    if (!is_valid_string(str, max_len)) {
        str[0] = '\0';
        return;
    }

    int len = strlen(str);
    if (len == 0) return;

    str[0] = toupper((unsigned char) str[0]);
    if (len > 1) {
        str[len - 1] = toupper((unsigned char) str[len - 1]);
    }

    for (int i = 1; i < len - 1; i++) {
        if (str[i - 1] == ' ' && str[i] != ' ') {
            str[i] = toupper((unsigned char) str[i]);
        }
        if (str[i + 1] == ' ' && str[i] != ' ') {
            str[i] = toupper((unsigned char) str[i]);
        }
    }
}

int main() {
    char str[] = "hello world example";
    printf("Original: %s\n", str);
    capitalize_first_last(str, sizeof(str));
    printf("Capitalized: %s\n", str);
    return 0;
}