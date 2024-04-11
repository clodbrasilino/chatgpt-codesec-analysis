#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeLowercase(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!islower(str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "HelloWorld";
    removeLowercase(str);
    printf("%s", str);
    return 0;
}