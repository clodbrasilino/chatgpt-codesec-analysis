#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_vowel(char c) {
    c = tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int count_chars_with_vowel_neighbors(const char *str, size_t max_len) {
    int count = 0;
    size_t len;
    size_t i;
    
    if (str == NULL) {
        return 0;
    }
    
    len = strnlen(str, max_len);
    
    if (len < 2) {
        return 0;
    }
    
    for (i = 0; i < len; i++) {
        int has_vowel_neighbor = 0;
        
        if (i > 0 && is_vowel(str[i - 1])) {
            has_vowel_neighbor = 1;
        }
        
        if (i < len - 1 && is_vowel(str[i + 1])) {
            has_vowel_neighbor = 1;
        }
        
        if (has_vowel_neighbor) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    size_t buffer_size = 0;
    char *str = NULL;
    ssize_t read_len;
    int result;
    
    printf("Enter a string: ");
    
    read_len = getline(&str, &buffer_size, stdin);
    
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }
    
    if (read_len > 0 && str[read_len - 1] == '\n') {
        str[read_len - 1] = '\0';
    }
    
    result = count_chars_with_vowel_neighbors(str, (size_t)read_len);
    
    printf("Count: %d\n", result);
    
    free(str);
    
    return 0;
}