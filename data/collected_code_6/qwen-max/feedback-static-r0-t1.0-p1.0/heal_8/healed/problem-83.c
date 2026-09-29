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
    size_t length = strlen(input);

    if (length > 0) {
        char result = addChars(input, length - 1);
        printf("Resulting character: %c\n", result);
    } else {
        fprintf(stderr, "Input string is not valid.\n");
        return 1;
    }
    return 0;
}