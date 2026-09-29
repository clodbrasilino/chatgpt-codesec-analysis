#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

size_t count_lowercase_letters(const char *str) {
    size_t count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (*str != '\0') {
        if (islower((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    
    return count;
}

int main(void) {
    const char *test_string = "Hello, World! This is a Test String with Lowercase Letters.";
    size_t lowercase_count;
    
    lowercase_count = count_lowercase_letters(test_string);
    
    printf("Number of lowercase letters: %zu\n", lowercase_count);
    
    return 0;
}