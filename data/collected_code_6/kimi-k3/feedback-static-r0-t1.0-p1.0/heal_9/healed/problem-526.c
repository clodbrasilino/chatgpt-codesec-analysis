#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

int capitalize_first_last(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return -1;
    }
    
    size_t len = strnlen(str, size);
    if (len >= size) {
        return -1;
    }
    
    size_t i = 0;
    while (i < len) {
        if (!isspace((unsigned char)str[i])) {
            size_t start = i;
            size_t end = i;
            
            while (end < len && !isspace((unsigned char)str[end])) {
                end++;
            }
            
            if (end > start) {
                str[start] = (char)toupper((unsigned char)str[start]);
                if (end - 1 > start) {
                    str[end - 1] = (char)toupper((unsigned char)str[end - 1]);
                }
            }
            
            i = end;
        } else {
            i++;
        }
    }
    
    return 0;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        int c;
        bool overflow = false;
        while ((c = getchar()) != '\n' && c != EOF) {
            overflow = true;
        }
        if (overflow) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }
    
    if (capitalize_first_last(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}