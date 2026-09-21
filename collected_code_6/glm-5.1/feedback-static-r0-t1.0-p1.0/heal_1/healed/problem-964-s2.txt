#include <stdio.h>
#include <stdbool.h>

bool is_length_even(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }

    size_t len = 0;
    while (len < max_len && word[len] != '\0') {
        len++;
    }

    if (len == 0 || len == max_len) {
        return false;
    }

    return len % 2 == 0;
}

int main(void) {
    const char *test_word = "hello";
    size_t max_len = 1024;

    if (is_length_even(test_word, max_len)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}