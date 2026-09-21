#include <stdio.h>
#include <string.h>

void remove_first_last_occurrence(char *str, char ch) {
    if (str == NULL || *str == '\0') return;

    size_t len = strlen(str);

    for (size_t i = 0; i < len; ++i) {
        if (str[i] == ch) {
            memmove(str, str + 1, len - i);
            --len;
            break;
        }
    }

    for (size_t i = 0; i < len; ++i) {
        if (str[i] == ch) {
            memmove(&str[i], &str[i + 1], len - i);
            str[len - 1] = '\0';
            break;
        }
    }
}

int main() {
    char str[] = "hello world";
    char ch = 'o';

    printf("Original string: %s\n", str);
    remove_first_last_occurrence(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}