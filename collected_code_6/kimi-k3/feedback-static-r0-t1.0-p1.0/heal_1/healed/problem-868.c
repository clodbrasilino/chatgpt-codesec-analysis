#include <stdio.h>
#include <string.h>

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
    char buffer[1024];
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        printf("%d\n", lengthOfLastWord(buffer, len));
    }
    
    return 0;
}