#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* replace_char(char* str, char old_char, char new_char) {
    if (str == NULL) {
        return NULL;
    }

    char* current = str;
    while (*current != '\0') {
        if (*current == old_char) {
            *current = new_char;
        }
        current++;
    }
    return str;
}

int main(void) {
    char buffer[100];
    char old_char, new_char;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Enter character to replace: ");
    if (scanf(" %c", &old_char) != 1) {
        fprintf(stderr, "Error reading old character\n");
        return 1;
    }

    printf("Enter replacement character: ");
    if (scanf(" %c", &new_char) != 1) {
        fprintf(stderr, "Error reading new character\n");
        return 1;
    }

    char* result = replace_char(buffer, old_char, new_char);
    if (result == NULL) {
        fprintf(stderr, "Error: NULL string\n");
        return 1;
    }

    printf("Result: %s\n", result);

    return 0;
}