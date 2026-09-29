#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char new_char) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = new_char;
        }
    }
}

int main() {
    char input[100];
    char replacement;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';
    }

    printf("Enter the character to replace spaces with: ");
    scanf(" %c", &replacement);
    getchar();

    replace_spaces(input, replacement);

    printf("Modified string: %s\n", input);

    return 0;
}