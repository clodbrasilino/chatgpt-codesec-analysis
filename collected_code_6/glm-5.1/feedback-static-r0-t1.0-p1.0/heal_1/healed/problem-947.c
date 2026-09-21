#include <stdio.h>
#include <limits.h>
#include <ctype.h>

int shortest_word_length(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    int min_len = INT_MAX;
    int current_len = 0;

    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }

        if (isalnum((unsigned char)str[i])) {
            current_len++;
        } else {
            if (current_len > 0) {
                if (current_len < min_len) {
                    min_len = current_len;
                }
                current_len = 0;
            }
        }
    }

    if (current_len > 0) {
        if (current_len < min_len) {
            min_len = current_len;
        }
    }

    if (min_len == INT_MAX) {
        return 0;
    }

    return min_len;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    int result = shortest_word_length(text, 1024);

    printf("%d\n", result);

    return 0;
}