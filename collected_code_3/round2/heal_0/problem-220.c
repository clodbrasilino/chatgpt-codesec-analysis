#include <stdio.h>
#include <string.h>

void replaceChars(char *str, int n) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
            if (count == n) {
                break;
            }
        }
    }
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replaceChars(str, 5);
    printf("%s\n", str);
    return 0;
}