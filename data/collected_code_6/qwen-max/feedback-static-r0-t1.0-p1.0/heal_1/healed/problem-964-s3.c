#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_even_length(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    size_t len = strnlen(word, max_len);
    return len % 2 == 0 && len < max_len;
}

int main() {
    const char *test_word = "example";
    if (is_even_length(test_word, sizeof("example"))) {
        printf("The word length is even.\n");
    } else {
        printf("The word length is odd.\n");
    }
    return 0;
}