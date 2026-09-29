#include <stdio.h>
#include <string.h>

int longest_word_length(const char *str) {
    int max_len = 0, current_len = 0;
    while (*str) {
        if (*str == ' ' || *str == '\t' || *str == '\n') {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        } else {
            current_len++;
        }
        str++;
    }
    if (current_len > max_len) {
        max_len = current_len;
    }
    return max_len;
}

int main() {
    const char *sentence = "The quick brown fox jumps over the lazy dog";
    int length = longest_word_length(sentence);
    printf("Length of the longest word: %d\n", length);
    return 0;
}