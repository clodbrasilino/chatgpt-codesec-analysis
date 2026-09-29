#include <stdio.h>
#include <string.h>

int is_word_length_even(const char *word, size_t max_len) {
    if (word == NULL || max_len == 0) {
        return 0;
    }
    size_t length = strnlen(word, max_len);
    return (length % 2 == 0) ? 1 : 0;
}

int main() {
    const char *test_word = "example";
    int result = is_word_length_even(test_word, sizeof("example") - 1);
    if (result) {
        printf("The word length is even.\n");
    } else {
        printf("The word length is odd.\n");
    }
    return 0;
}