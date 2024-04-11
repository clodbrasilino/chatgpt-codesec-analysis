#include <stdio.h>
#include <string.h>

void remove_spaces(char* str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ') {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main() {
    char str[] = "Hello, this is a test string.";
    remove_spaces(str);
    printf("%s", str);
    return 0;
}