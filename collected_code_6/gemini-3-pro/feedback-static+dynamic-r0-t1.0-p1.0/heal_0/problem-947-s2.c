#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

size_t find_shortest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t min_len = ULONG_MAX;
    size_t current_len = 0;
    int in_word = 0;
    const char *ptr = str;

    while (*ptr != '\0') {
        if (!isspace((unsigned char)*ptr)) {
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
        ptr++;
    }

    if (in_word) {
        if (current_len < min_len) {
            min_len = current_len;
        }
    }

    return (min_len == ULONG_MAX) ? 0 : min_len;
}

int main(void) {
    const char *test_str = "Find the length of the shortest word here";
    size_t shortest_len = find_shortest_word_length(test_str);
    
    printf("Length of the shortest word: %zu\n", shortest_len);
    
    return EXIT_SUCCESS;
}