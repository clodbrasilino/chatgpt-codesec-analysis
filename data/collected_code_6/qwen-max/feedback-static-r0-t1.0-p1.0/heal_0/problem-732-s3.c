#include <stdio.h>
#include <string.h>

void replace_chars(char *str) {
    if (str == NULL) return;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main() {
    char input[] = "Hello, World. This is a test.";
    replace_chars(input);
    printf("%s\n", input);
    return 0;
}