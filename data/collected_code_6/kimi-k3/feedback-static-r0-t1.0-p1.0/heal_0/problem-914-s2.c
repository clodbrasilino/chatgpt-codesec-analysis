#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

bool isAlternating(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strlen(str);
    
    if (len < 2) {
        return false;
    }
    
    char first = str[0];
    char second = str[1];
    
    if (first == second) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        char expected = (i % 2 == 0) ? first : second;
        if (str[i] != expected) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    char buffer[MAX_INPUT_SIZE];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (isAlternating(buffer)) {
        printf("The string is made up of two alternating characters.\n");
    } else {
        printf("The string is NOT made up of two alternating characters.\n");
    }
    
    return EXIT_SUCCESS;
}