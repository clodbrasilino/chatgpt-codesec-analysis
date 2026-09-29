#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        } else if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';  // Remove newline character
        toggle_case(input);
        printf("Toggled case: %s\n", input);
    }
    return 0;
}