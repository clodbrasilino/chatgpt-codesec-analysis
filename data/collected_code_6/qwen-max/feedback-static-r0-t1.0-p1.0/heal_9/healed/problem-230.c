#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, size_t len, char new_char) {
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == ' ') {
            str[i] = new_char;
        }
    }
}

int main() {
    char input[100];
    char replacement;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        size_t input_len = strnlen(input, sizeof(input));
        if (input_len > 0 && input_len < sizeof(input)) {
            printf("Enter the character to replace spaces with: ");
            if (scanf(" %c", &replacement) == 1) {
                replace_spaces(input, input_len, replacement);
                printf("Modified string: %s\n", input);
            } else {
                printf("Invalid input for replacement character.\n");
            }
        } else {
            printf("Input is too long or empty.\n");
        }
    } else {
        printf("Failed to read input.\n");
    }

    return 0;
}