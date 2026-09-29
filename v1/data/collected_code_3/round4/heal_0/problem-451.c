#include <stdio.h>
#include <ctype.h>

void remove_spaces(char* str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (!isspace(str[i])) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main() {
    char str[] = "Hello, World! This is a test string.";
    remove_spaces(str);
    printf("%s\n", str);
    return 0;
}