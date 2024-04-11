#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeNonAlphanumeric(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (isalnum(str[i]))
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "Hello, World! 123";
    removeNonAlphanumeric(str);
    printf("%s\n", str);
    return 0;
}