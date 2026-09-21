#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void replace_spaces(char *str, size_t size, char replacement) {
    if (str == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to replace_spaces\n");
        return;
    }

    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return;
    }

    if (size == 0) {
        fprintf(stderr, "Error: Buffer size cannot be zero\n");
        return;
    }

    size_t i = 0;
    while (i < size && str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
        i++;
    }
}

int main(void) {
    char buffer[256];
    char replacement;
    size_t input_len;
    
    memset(buffer, 0, sizeof(buffer));
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input_len = strnlen(buffer, sizeof(buffer));
    if (input_len > 0 && buffer[input_len - 1] == '\n') {
        buffer[input_len - 1] = '\0';
    } else {
        if (input_len >= sizeof(buffer) - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
    }
    
    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        fprintf(stderr, "Error reading replacement character\n");
        return EXIT_FAILURE;
    }
    
    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return EXIT_FAILURE;
    }
    
    replace_spaces(buffer, sizeof(buffer), replacement);
    printf("Modified string: %s\n", buffer);
    
    return EXIT_SUCCESS;
}