#include <stdio.h>
#include <string.h>

char addChars(const char *str, size_t len) {
    int sum = 0;
    for (size_t i = 0; i < len; ++i) {
        sum += (unsigned char)str[i];
    }
    return (char)(sum % 256);
}

int main() {
    const char input[] = "Hello, World!";
    size_t input_len = sizeof(input) - 1;
    char result = addChars(input, input_len);
    printf("Resulting character: %c\n", result);
    return 0;
}