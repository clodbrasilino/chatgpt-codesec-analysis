#include <stdio.h>
#include <ctype.h>
#include <string.h>

int validate_string(const char *str, size_t min_len, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strlen(str);
    if (len < min_len || len > max_len) {
        return 0;
    }
    
    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            has_upper = 1;
        }
        if (islower((unsigned char)str[i])) {
            has_lower = 1;
        }
        if (isdigit((unsigned char)str[i])) {
            has_digit = 1;
        }
    }
    
    return has_upper && has_lower && has_digit;
}

int main(void) {
    const char *test_strings[] = {
        "Abc123",
        "abc123",
        "ABC123",
        "Abcdef",
        "A1",
        "Ab1"
    };
    
    for (int i = 0; i < 6; i++) {
        printf("%s: %d\n", test_strings[i], validate_string(test_strings[i], 3, 10));
    }
    
    return 0;
}