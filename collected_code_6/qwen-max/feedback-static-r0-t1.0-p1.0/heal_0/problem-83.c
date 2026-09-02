#include <stdio.h>
#include <string.h>

char addChars(const char *str) {
    int sum = 0;
    for (int i = 0; i < strlen(str); ++i) {
        sum += str[i];
    }
    return (char)(sum % 256);
}

int main() {
    const char *input = "Hello, World!";
    char result = addChars(input);
    printf("Resulting character: %c\n", result);
    return 0;
}