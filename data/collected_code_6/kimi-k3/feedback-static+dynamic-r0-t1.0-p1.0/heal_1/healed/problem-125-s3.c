#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int find_max_diff(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    
    int max_diff = 0;
    int current_diff = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '0') {
            current_diff++;
        } else if (str[i] == '1') {
            current_diff--;
        } else {
            return 0;
        }
        
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
        
        if (current_diff < 0) {
            current_diff = 0;
        }
    }
    
    return max_diff;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;
    
    len = getline(&buffer, &buffer_size, stdin);
    
    if (len != -1) {
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        int result = find_max_diff(buffer, (size_t)len);
        printf("%d\n", result);
        
        free(buffer);
    }
    
    return 0;
}