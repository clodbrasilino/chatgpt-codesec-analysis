#include <stdio.h>
#include <string.h>

int is_odd_length(const char *word, size_t max_len) {
    if (word == NULL) {
        return -1;
    }
    size_t length = strnlen(word, max_len);
    return length % 2;
}

int main() {
    const char *test_word = "hello";
    int result = is_odd_length(test_word, sizeof("hello"));
    if (result == 1) {
        printf("The length of the word is odd.\n");
    } else if (result == 0) {
        printf("The length of the word is even.\n");
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}