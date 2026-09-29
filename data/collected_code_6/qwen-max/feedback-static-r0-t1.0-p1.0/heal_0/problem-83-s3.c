#include <stdio.h>
#include <string.h>

char sum_of_chars(const char *str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        sum += (unsigned char)str[i];
    }
    return (char)(sum % 256);
}

int main() {
    const char *input = "example";
    char result = sum_of_chars(input);
    printf("The resulting character is: %c\n", result);
    return 0;
}