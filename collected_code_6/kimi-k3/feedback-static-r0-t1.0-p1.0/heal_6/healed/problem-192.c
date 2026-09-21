#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

bool has_letter_and_number(const char *str) {
    bool has_letter = false;
    bool has_number = false;
    
    if (str == NULL) {
        return false;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            has_letter = true;
        } else if (isdigit(c)) {
            has_number = true;
        }
        if (has_letter && has_number) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strcspn(buffer, "\n");
        buffer[len] = '\0';
        
        if (has_letter_and_number(buffer)) {
            printf("String contains at least one letter and one number.\n");
        } else {
            printf("String does not contain both a letter and a number.\n");
        }
    } else {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    
    return 0;
}