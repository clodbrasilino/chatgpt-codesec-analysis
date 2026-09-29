#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(char *str) {
    int i = 0, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (i == 0 || (i > 0 && str[i - 1] == ' ') || (i < len - 1 && str[i + 1] == ' ')) {
            str[i] = toupper(str[i]);
        }
        if (i > 0 && (i == len - 1 || str[i + 1] == ' ')) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    char input[256];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character if present
    capitalize_first_last(input);
    printf("Capitalized: %s\n", input);
    return 0;
}