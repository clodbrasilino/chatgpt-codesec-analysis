#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

int find_longest_word_length(const char *str)
{
    int max_length = 0;
    int current_length = 0;
    
    if (str == NULL) {
        return -1;
    }
    
    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            if (current_length < INT_MAX) {
                current_length++;
            }
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        str++;
    }
    
    if (current_length > max_length) {
        max_length = current_length;
    }
    
    return max_length;
}

int main(void)
{
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    int result;
    
    printf("Enter a string: ");
    
    bytes_read = getline(&input, &buffer_size, stdin);
    
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    if (bytes_read > 0 && input[bytes_read - 1] == '\n') {
        input[bytes_read - 1] = '\0';
    }
    
    result = find_longest_word_length(input);
    
    if (result < 0) {
        fprintf(stderr, "Error: Invalid input\n");
        free(input);
        return 1;
    }
    
    printf("Length of longest word: %d\n", result);
    
    free(input);
    
    return 0;
}