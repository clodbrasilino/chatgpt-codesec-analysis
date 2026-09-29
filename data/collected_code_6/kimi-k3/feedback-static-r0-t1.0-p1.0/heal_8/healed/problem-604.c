#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

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
    const char *str_end = str + len;
    
    while (current < str_end) {
        if (word_start == NULL && !isspace((unsigned char)*current)) {
            word_start = current;
        }
        if (word_start != NULL && 
            (current + 1 >= str_end || 
             isspace((unsigned char)*(current + 1)) || 
             *(current + 1) == '\0')) {
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
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;
    
    if ((len = getline(&buffer, &buffer_size, stdin)) == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (!reverse_words(buffer, (size_t)len + 1)) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (printf("%s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}