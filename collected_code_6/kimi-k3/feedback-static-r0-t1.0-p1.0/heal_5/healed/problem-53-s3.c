#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

bool check_first_last_equal(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }
    
    return str[0] == str[len - 1];
}

int main(void) {
    char buffer[BUFFER_SIZE];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("First and last characters are not equal.\n");
        return EXIT_SUCCESS;
    }
    
    if (check_first_last_equal(buffer, len)) {
        printf("First and last characters are equal.\n");
    } else {
        printf("First and last characters are not equal.\n");
    }
    
    return EXIT_SUCCESS;
}