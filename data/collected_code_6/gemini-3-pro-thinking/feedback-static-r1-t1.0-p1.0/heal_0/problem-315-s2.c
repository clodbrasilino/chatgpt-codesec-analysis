#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

size_t find_first_max_even_word_length(const char *str) {
    if (!str) {
        return 0;
    }

    size_t max_len = 0;
    size_t current_len = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            current_len++;
        } else {
            if (current_len > 0) {
                if (current_len % 2 == 0 && current_len > max_len) {
                    max_len = current_len;
                }
                current_len = 0;
            }
        }
    }

    if (current_len > 0) {
        if (current_len % 2 == 0 && current_len > max_len) {
            max_len = current_len;
        }
    }

    return max_len;
}

int main(void) {
    const char *test_string = "Be sure to write secure and robust code";
    size_t max_even_len = find_first_max_even_word_length(test_string);
    
    printf("%zu\n", max_even_len);
    
    return 0;
}