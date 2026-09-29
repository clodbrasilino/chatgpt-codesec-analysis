#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validate_string(const char *str, size_t min_length) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strlen(str);
    if (len < min_length) {
        return false;
    }
    
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        }
    }
    
    return has_upper && has_lower && has_digit;
}

int main(void) {
    char buffer[256];
    size_t min_len = 8;
    
    printf("Enter string to validate: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (validate_string(buffer, min_len)) {
        printf("String is valid\n");
    } else {
        printf("String is invalid\n");
    }
    
    return 0;
}