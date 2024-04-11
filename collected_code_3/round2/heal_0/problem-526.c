#include <ctype.h>
#include <stdio.h>
#include <string.h>

void capitalizeFirstAndLast(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (i == 0 || str[i - 1] == ' ') {
            str[i] = toupper(str[i]);
        }
        if (i == len - 1 || str[i + 1] == ' ') {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    char str[] = "hello world";
    capitalizeFirstAndLast(str);
    printf("%s\n", str);
    return 0;
}