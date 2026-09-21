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
    
    if (str == NULL || max_len == 0) {
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
    char *str = NULL;
    size_t size = 0;
    ssize_t nread;
    int result;
    
    printf("Enter a string: ");
    
    nread = getline(&str, &size, stdin);
    
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }
    
    if (nread > 0 && str[nread - 1] == '\n') {
        str[nread - 1] = '\0';
        nread--;
    }
    
    result = count_chars_with_vowel_neighbors(str, (size_t)nread);
    
    printf("Count: %d\n", result);
    
    free(str);
    
    return 0;
}