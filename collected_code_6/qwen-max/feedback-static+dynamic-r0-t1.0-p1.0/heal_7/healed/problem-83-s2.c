#include <stdio.h>
#include <string.h>

int sum_of_chars(const char *str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        sum += (unsigned char)str[i];
    }
    return sum;
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        int result = sum_of_chars(input);
        printf("Sum of characters: %d\n", result);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}