#include <stdio.h>
#include <string.h>

void removeOddChars(char *str) {
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (i % 2 == 0) str[j++] = str[i];
    }
    str[j] = '\0';
}

int main() {
    char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    removeOddChars(str);
    printf("%s", str);
    return 0;
}