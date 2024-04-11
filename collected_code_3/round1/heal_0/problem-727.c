#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_special_characters(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (isalnum(str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "Hello, World! 123";
    remove_special_characters(str);
    printf("%s\n", str);
    return 0;
}