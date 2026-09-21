#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

void reverse_substring(char *start, char *end) {
    if (start == NULL || end == NULL || start >= end) {
        return;
    }
    
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

bool reverse_words(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return false;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0 || len >= max_len) {
        return false;
    }
    
    char *word_start = NULL;
    char *current = str;
    char *str_end = str + len;
    
    while (current < str_end && *current != '\0') {
        if (word_start == NULL && !isspace((unsigned char)*current)) {
            word_start = current;
        }
        if (word_start != NULL && 
            (current + 1 >= str_end || 
             isspace((unsigned char)*(current + 1)) || 
             *(current + 1) == '\0')) {
            if (current >= str_end) {
                return false;
            }
            reverse_substring(word_start, current);
            word_start = NULL;
        }
        current++;
    }
    
    if (current > str) {
        reverse_substring(str, current - 1);
    }
    
    return true;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len >= sizeof(buffer)) {
        return EXIT_FAILURE;
    }
    
    size_t newline_pos = strcspn(buffer, "\n");
    if (newline_pos < sizeof(buffer)) {
        buffer[newline_pos] = '\0';
    }
    
    if (!reverse_words(buffer, sizeof(buffer))) {
        return EXIT_FAILURE;
    }
    
    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}