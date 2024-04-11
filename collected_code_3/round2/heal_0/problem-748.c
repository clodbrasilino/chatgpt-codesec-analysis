#include <stdio.h>
#include <ctype.h>
#include <string.h>

void addSpaces(char* str) {
    int n = strlen(str);
    char result[2*n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (isupper(str[i]) && i != 0) {
            result[j++] = ' ';
        }
        result[j++] = str[i];
    }
    result[j] = '\0';
    printf("%s\n", result);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    addSpaces(str);
    return 0;
}