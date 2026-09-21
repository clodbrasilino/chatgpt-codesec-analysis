#include <stdio.h>
#include <string.h>
#include <ctype.h>

void to_lower_case(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        to_lower_case(input);
        printf("Lowercase string: %s\n", input);
    }
    return 0;
}