#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

char first_non_repeated_char(const char *str) {
    int char_count[UCHAR_MAX + 1] = {0};
    size_t i;
    
    if (str == NULL) {
        return '\0';
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        char_count[(unsigned char)str[i]]++;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (char_count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }
    
    return '\0';
}

int main(void) {
    char *input = NULL;
    size_t input_size = MAX_INPUT_SIZE;
    ssize_t bytes_read;
    char result;
    
    printf("Enter a string: ");
    
    input = (char *)malloc(input_size * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    bytes_read = getline(&input, &input_size, stdin);
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    if (bytes_read > 0 && input[bytes_read - 1] == '\n') {
        input[bytes_read - 1] = '\0';
    }
    
    result = first_non_repeated_char(input);
    
    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found\n");
    }
    
    free(input);
    return 0;
}