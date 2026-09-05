#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

size_t shortest_word_length(const char *str) {
    size_t current_len = 0;
    size_t min_len = SIZE_MAX;

    if (str == NULL) {
        return 0;
    }

    while (*str) {
        if (*str == ' ' || *str == '\t' || *str == '\n') {
            if (current_len > 0) {
                if (current_len < min_len) {
                    min_len = current_len;
                }
                current_len = 0;
            }
        } else {
            current_len++;
        }
        str++;
    }

    if (current_len > 0) {
        if (current_len < min_len) {
            min_len = current_len;
        }
    }

    if (min_len == SIZE_MAX) {
        return 0;
    }

    return min_len;
}

int main(int argc, char const * const argv[]) {
    if (argc > 1) {
        size_t result = shortest_word_length(argv[1]);
        printf("%zu\n", result);
    } else {
        const char *text = "The quick brown fox jumps over the lazy dog";
        size_t result = shortest_word_length(text);
        printf("%zu\n", result);
    }
    
    return EXIT_SUCCESS;
}