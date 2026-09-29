#include <stdio.h>

void replace_chars(char *str, size_t n) {
    if (str == NULL || n == 0) {
        return;
    }
    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
            if (count == n) {
                break;
            }
        }
    }
}

int main(void) {
    char text[] = "hello, world. this is a test, with spaces.";
    printf("Original: %s\n", text);
    replace_chars(text, 3);
    printf("Modified: %s\n", text);
    return 0;
}