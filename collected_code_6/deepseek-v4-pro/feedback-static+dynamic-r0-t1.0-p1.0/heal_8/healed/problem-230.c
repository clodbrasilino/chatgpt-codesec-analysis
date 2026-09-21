#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        if (*str == ' ') {
            *str = replacement;
        }
        str++;
    }
}

int main(void) {
    char *str = NULL;
    size_t buffer_size = 256;
    char replacement;
    
    str = malloc(buffer_size);
    if (str == NULL) {
        return 1;
    }
    
    printf("Enter a string: ");
    if (fgets(str, buffer_size, stdin) == NULL) {
        free(str);
        return 1;
    }
    
    size_t len = strcspn(str, "\n");
    if (len < buffer_size && str[len] == '\n') {
        str[len] = '\0';
    } else {
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        }
    }
    
    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        free(str);
        return 1;
    }
    
    replace_spaces(str, replacement);
    
    printf("Modified string: %s\n", str);
    
    free(str);
    return 0;
}