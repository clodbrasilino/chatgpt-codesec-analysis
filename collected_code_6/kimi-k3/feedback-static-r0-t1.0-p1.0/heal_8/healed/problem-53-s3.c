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
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;
    
    printf("Enter a string: ");
    
    len = getline(&buffer, &buffer_size, stdin);
    
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("First and last characters are not equal.\n");
        free(buffer);
        return EXIT_SUCCESS;
    }
    
    if (check_first_last_equal(buffer, (size_t)len)) {
        printf("First and last characters are equal.\n");
    } else {
        printf("First and last characters are not equal.\n");
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}