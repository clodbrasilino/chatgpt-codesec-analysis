#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validate_string(const char *str, size_t min_length) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strnlen(str, 257);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[258];
    size_t min_len = 8;
    
    printf("Enter string to validate: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
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