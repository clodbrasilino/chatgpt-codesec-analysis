#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

int total_ascii_value(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int total = 0;
    size_t i = 0;
    
    while (i < 256 && str[i] != '\0') {
        total += (unsigned char)str[i];
        i++;
    }
    
    return total;
}

int main(void) {
    char *str = NULL;
    size_t buffer_size = 256;
    
    str = (char *)malloc(buffer_size);
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter a string: ");
    if (fgets(str, (int)buffer_size, stdin) == NULL) {
        str[0] = '\0';
    } else {
        size_t len = strnlen(str, buffer_size);
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        } else if (len == buffer_size - 1 && str[len - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                if (c == EOF) break;
            }
        }
    }
    
    int result = total_ascii_value(str);
    printf("Total ASCII value: %d\n", result);
    
    free(str);
    return 0;
}