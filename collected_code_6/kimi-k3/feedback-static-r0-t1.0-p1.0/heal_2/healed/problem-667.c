#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

static bool is_vowel(char c)
{
    char lower_c = (char)tolower((unsigned char)c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || 
            lower_c == 'o' || lower_c == 'u');
}

size_t count_vowels(const char *str)
{
    size_t count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (*str != '\0') {
        if (is_vowel(*str)) {
            count++;
        }
        str++;
    }
    
    return count;
}

int main(void)
{
    char *input = malloc(MAX_INPUT_SIZE);
    size_t vowel_count;
    size_t len;
    
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter a string: ");
    
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    len = strnlen(input, MAX_INPUT_SIZE);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    vowel_count = count_vowels(input);
    printf("Number of vowels: %zu\n", vowel_count);
    
    free(input);
    return 0;
}