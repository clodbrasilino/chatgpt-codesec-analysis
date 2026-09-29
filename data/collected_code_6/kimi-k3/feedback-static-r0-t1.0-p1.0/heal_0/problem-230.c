#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        return;
    }
    
    size_t i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main(void) {
    char buffer[256];
    char replacement;
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    printf("Enter replacement character: ");
    int c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error reading replacement character\n");
        return EXIT_FAILURE;
    }
    replacement = (char)c;
    
    replace_spaces(buffer, replacement);
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}