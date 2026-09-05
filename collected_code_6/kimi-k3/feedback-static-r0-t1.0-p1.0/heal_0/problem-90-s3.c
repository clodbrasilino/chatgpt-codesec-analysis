#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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
    char input[1024];
    int result;
    
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    result = find_longest_word_length(input);
    
    if (result < 0) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    printf("Length of longest word: %d\n", result);
    
    return 0;
}