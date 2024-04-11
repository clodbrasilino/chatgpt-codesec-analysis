#include <stdio.h>
#include <ctype.h>
#include <string.h>

void remove_non_alphanumeric(char *str) {
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
    remove_non_alphanumeric(str);
    printf("%s\n", str);
    return 0;
}