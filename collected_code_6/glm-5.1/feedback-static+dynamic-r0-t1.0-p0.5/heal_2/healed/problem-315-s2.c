#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_first_max_max_even_word(const char *str, size_t max_read) {
    if (str == NULL) {
        return -1;
    }

    int max_len = 0;
    int current_len = 0;
    int in_word = 0;
    size_t len = strnlen(str, max_read);

    for (size_t i = 0; i <= len; i++) {
        if (str[i] != ' ' && str[i] != '\0') {
            current_len++;
            in_word = 1;
        } else {
            if (in_word) {
                if (current_len % 2 == 0) {
                    if (current_len > max_len) {
                        max_len = current_len;
                    }
                }
                current_len = 0;
                in_word = 0;
            }
        }
    }

    return max_len;
}

int main(void) {
    const char *text = "This is a test string with some evenlength words";
    int result = find_first_max_max_even_word(text, 256);

    printf("%d\n", result);

    return 0;
}