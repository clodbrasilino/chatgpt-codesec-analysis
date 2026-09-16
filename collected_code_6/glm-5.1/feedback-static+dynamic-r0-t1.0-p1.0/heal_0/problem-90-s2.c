#include <stdio.h>
#include <ctype.h>

int find_longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;

    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        str++;
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main() {
    const char *text = "The quick brown fox jumps over the lazy dog";
    int length = find_longest_word_length(text);
    printf("%d\n", length);
    return 0;
}