#include <stdio.h>
#include <string.h>

char sum_of_chars(const char *str) {
    long sum = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        sum += (unsigned char)str[i];
    }
    return (char)(sum % 256);
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Failed to read input.\n");
        return 1;
    }
    size_t len = strcspn(input, "\n");
    if (len >= sizeof(input) - 1) {
        printf("Input too long.\n");
        return 1;
    }
    if (input[len] == '\n') {
        input[len] = '\0';
    } else {
        input[sizeof(input) - 1] = '\0';
    }
    char result = sum_of_chars(input);
    printf("Sum of characters: %d\n", (int)result);
    return 0;
}