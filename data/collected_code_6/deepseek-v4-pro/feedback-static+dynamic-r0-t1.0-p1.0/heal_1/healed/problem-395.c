#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 256

char find_first_non_repeated_char(const char *str) {
    int count[TABLE_SIZE] = {0};
    
    if (str == NULL) {
        return '\0';
    }
    
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        count[i] = 0;
    }
    
    const char *ptr = str;
    while (*ptr != '\0') {
        count[(unsigned char)*ptr]++;
        ptr++;
    }
    
    ptr = str;
    while (*ptr != '\0') {
        if (count[(unsigned char)*ptr] == 1) {
            return *ptr;
        }
        ptr++;
    }
    
    return '\0';
}

int main(void) {
    char input[256];
    size_t max_input = sizeof(input) - 1;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input[max_input] = '\0';
    
    size_t len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }
    
    if (len == 0) {
        input[0] = '\0';
    } else if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    char result = find_first_non_repeated_char(input);
    
    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found\n");
    }
    
    return EXIT_SUCCESS;
}