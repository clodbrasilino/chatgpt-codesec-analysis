#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    int length = 0;
    size_t i = 0;
    
    if (s == NULL || max_len == 0) {
        return 0;
    }
    
    while (i < max_len && s[i] != '\0') {
        i++;
    }
    
    if (i == 0) {
        return 0;
    }
    
    i--;
    
    while (i > 0 && s[i] == ' ') {
        i--;
    }
    
    if (s[i] == ' ') {
        return 0;
    }
    
    while (i > 0 && s[i] != ' ') {
        length++;
        i--;
    }
    
    if (s[i] != ' ') {
        length++;
    }
    
    return length;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    
    read_len = getline(&buffer, &buffer_size, stdin);
    
    if (read_len != -1) {
        size_t len = (size_t)read_len;
        
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        printf("%d\n", lengthOfLastWord(buffer, len));
    }
    
    free(buffer);
    return 0;
}