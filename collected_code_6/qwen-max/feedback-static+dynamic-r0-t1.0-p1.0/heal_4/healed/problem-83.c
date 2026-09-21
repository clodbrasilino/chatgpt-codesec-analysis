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
    const char *input = "Hello, World!";
    size_t input_len = strlen(input) + 1; // Include null-terminator
    char result = addChars(input, input_len - 1); // Exclude null-terminator from sum
    printf("Resulting character: %c\n", result);
    return 0;
}