#include <stdio.h>
#include <ctype.h>
#include <string.h>

size_t find_longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t max_len = 0;
    size_t current_len = 0;

    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            current_len++;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        }
        str++;
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    return max_len;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    size_t longest = find_longest_word_length(text);
    
    printf("Longest word length: %zu\n", longest);
    
    return 0;
}