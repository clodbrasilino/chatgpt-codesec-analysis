#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

void count_characters(const char *str, int *alphabets, int *digits, int *special) {
    if (str == NULL || alphabets == NULL || digits == NULL || special == NULL) {
        return;
    }
    
    *alphabets = 0;
    *digits = 0;
    *special = 0;
    
    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        
        if (isalpha(c)) {
            (*alphabets)++;
        } else if (isdigit(c)) {
            (*digits)++;
        } else {
            (*special)++;
        }
        str++;
    }
}

int main(void) {
    char *input = NULL;
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    int result = EXIT_FAILURE;
    
    input = (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter a string: ");
    
    if (fgets(input, MAX_INPUT_SIZE, stdin) != NULL) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        count_characters(input, &alphabets, &digits, &special);
        
        printf("Alphabets: %d\n", alphabets);
        printf("Digits: %d\n", digits);
        printf("Special characters: %d\n", special);
        
        result = EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Error reading input\n");
    }
    
    free(input);
    input = NULL;
    
    return result;
}