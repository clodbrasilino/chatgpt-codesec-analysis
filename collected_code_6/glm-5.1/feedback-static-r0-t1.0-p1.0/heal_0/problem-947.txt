#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

int shortest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    int min_len = INT_MAX;
    int current_len = 0;

    for (size_t i = 0; i <= len; i++) {
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

    if (min_len == INT_MAX) {
        return 0;
    }

    return min_len;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    int result = shortest_word_length(text);

    printf("%d\n", result);

    return 0;
}