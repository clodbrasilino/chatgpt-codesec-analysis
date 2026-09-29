#include <stdio.h>
#include <ctype.h>
#include <limits.h>

size_t get_shortest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t min_len = ULONG_MAX;
    size_t current_len = 0;
    int in_word = 0;

    while (*str != '\0') {
        if (!isspace((unsigned char)*str)) {
            current_len++;
            in_word = 1;
        } else {
            if (in_word) {
                if (current_len < min_len) {
                    min_len = current_len;
                }
                current_len = 0;
                in_word = 0;
            }
        }
        str++;
    }

    if (in_word) {
        if (current_len < min_len) {
            min_len = current_len;
        }
    }

    return (min_len == ULONG_MAX) ? 0 : min_len;
}

int main(void) {
    const char *text = "This is a test string to find the shortest word";
    size_t shortest_len = get_shortest_word_length(text);
    
    printf("Length of the shortest word: %zu\n", shortest_len);
    
    return 0;
}