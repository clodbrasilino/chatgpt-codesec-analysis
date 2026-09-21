#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_first_last_equal(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }
    
    return str[0] == str[len - 1];
}

int main(void) {
    char buffer[256];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("First and last characters are not equal.\n");
        return 0;
    }
    
    if (check_first_last_equal(buffer, len)) {
        printf("First and last characters are equal.\n");
    } else {
        printf("First and last characters are not equal.\n");
    }
    
    return 0;
}