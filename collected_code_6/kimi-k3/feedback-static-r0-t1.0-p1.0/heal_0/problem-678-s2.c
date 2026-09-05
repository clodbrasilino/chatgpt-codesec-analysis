#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool remove_spaces(char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t read_idx = 0;
    size_t write_idx = 0;
    size_t len = strlen(str);
    
    while (read_idx < len) {
        if (str[read_idx] != ' ') {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    
    str[write_idx] = '\0';
    return true;
}

int main(void) {
    char buffer[256];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (!remove_spaces(buffer)) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}