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
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
            input[len - 1] = '\0';
        } else {
            input[len] = '\0';
        }
        char result = sum_of_chars(input);
        printf("Sum of characters: %d\n", (int)result);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}