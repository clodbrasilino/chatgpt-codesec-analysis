#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char new_char) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = new_char;
        }
    }
}

int main() {
    char input[100];
    char replacement;

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove newline character

    printf("Enter the character to replace spaces with: ");
    scanf("%c", &replacement);

    replace_spaces(input, replacement);

    printf("Modified string: %s\n", input);

    return 0;
}