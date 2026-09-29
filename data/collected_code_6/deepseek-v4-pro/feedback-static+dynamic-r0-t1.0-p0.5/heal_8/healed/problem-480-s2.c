#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

char max_occurring_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }
    
    int *count = calloc(UCHAR_MAX + 1, sizeof(int));
    if (count == NULL) {
        return '\0';
    }
    
    const unsigned char *s = (const unsigned char *)str;
    
    while (*s) {
        count[*s]++;
        s++;
    }
    
    int max_count = 0;
    char max_char = '\0';
    
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_char = (char)i;
        }
    }
    
    free(count);
    return max_char;
}

int main(void) {
    char *str = NULL;
    size_t n = 0;
    
    printf("Enter a string: ");
    ssize_t bytes_read = getline(&str, &n, stdin);
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }
    
    if (bytes_read > 0 && str[bytes_read - 1] == '\n') {
        str[bytes_read - 1] = '\0';
    }
    
    char result = max_occurring_char(str);
    
    if (result == '\0') {
        printf("Empty string\n");
    } else {
        printf("Maximum occurring character: %c\n", result);
    }
    
    free(str);
    return 0;
}