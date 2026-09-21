#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str) {
    for (int i = 0; str[i] != '\0'; ++i) {
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
        size_t len = strcspn(input, "\n");
        if (len == sizeof(input) - 1) {
            input[sizeof(input) - 1] = '\0';
        } else {
            input[len] = '\0';
        }
        
        toggle_case(input);
        
        printf("Toggled case: %s\n", input);
    }

    return 0;
}