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
            current_length++;
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
    size_t input_size = 0;
    ssize_t line_length;
    int result;
    
    printf("Enter a string: ");
    
    line_length = getline(&input, &input_size, stdin);
    
    if (line_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    if (line_length > 0 && input[line_length - 1] == '\n') {
        input[line_length - 1] = '\0';
    }
    
    result = find_longest_word_length(input);
    
    free(input);
    
    if (result < 0) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    printf("Length of longest word: %d\n", result);
    
    return 0;
}