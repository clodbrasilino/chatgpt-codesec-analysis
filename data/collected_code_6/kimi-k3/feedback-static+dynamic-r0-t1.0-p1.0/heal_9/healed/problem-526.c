#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read;
    
    printf("Enter a string: ");
    read = getline(&buffer, &buffer_size, stdin);
    
    if (read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (read > 0 && buffer[read - 1] == '\n') {
        buffer[read - 1] = '\0';
    }
    
    if (capitalize_first_last(buffer, buffer_size) != 0) {
        fprintf(stderr, "Error processing string\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    printf("Result: %s\n", buffer);
    
    free(buffer);
    return EXIT_SUCCESS;
}