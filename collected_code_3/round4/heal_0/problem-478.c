#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* removeLowercase(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!islower(str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
    return str;
}

int main() {
    char str[] = "HelloWorld";
    printf("%s\n", removeLowercase(str));
    return 0;
}