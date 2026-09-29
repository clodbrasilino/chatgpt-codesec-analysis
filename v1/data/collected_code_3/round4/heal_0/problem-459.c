#include <stdio.h>
#include <ctype.h>
#include <string.h>

void remove_uppercase(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!isupper(str[i]) || str[i] == ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "Hello World";
    remove_uppercase(str);
    printf("%s\n", str);
    return 0;
}