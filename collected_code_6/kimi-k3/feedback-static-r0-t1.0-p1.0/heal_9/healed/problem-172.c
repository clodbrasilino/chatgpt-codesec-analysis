#include <stdio.h>
#include <string.h>

int count_std_occurrences(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return 0;
    }
    
    int count = 0;
    size_t len = strnlen(str, max_len);
    
    if (len < 3) {
        return 0;
    }
    
    for (size_t i = 0; i + 2 < len; i++) {
        if (str[i] == 's' && str[i + 1] == 't' && str[i + 2] == 'd') {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    char buffer[1024];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    buffer[sizeof(buffer) - 1] = '\0';
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    int result = count_std_occurrences(buffer, sizeof(buffer));
    
    printf("Occurrences of 'std': %d\n", result);
    
    return 0;
}