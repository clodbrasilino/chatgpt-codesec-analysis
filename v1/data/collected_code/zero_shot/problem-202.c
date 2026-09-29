#include <stdio.h>
#include <string.h>

void removeEvenChars(char* str) {
    int len = strlen(str);
    int i, j;
    for (i = 0, j = 0; i < len; i += 2, j++)
        str[j] = str[i];
    str[j] = '\0';
}

int main() {
    char str[] = "Hello World!";
    removeEvenChars(str);
    printf("%s\n", str);
    return 0;
}