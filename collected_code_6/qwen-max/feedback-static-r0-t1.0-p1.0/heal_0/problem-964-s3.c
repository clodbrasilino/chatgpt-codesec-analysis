#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_even_length(const char *word) {
    if (word == NULL) {
        return false;
    }
    size_t len = strlen(word);
    return len % 2 == 0;
}

int main() {
    const char *test_word = "example";
    if (is_even_length(test_word)) {
        printf("The word length is even.\n");
    } else {
        printf("The word length is odd.\n");
    }
    return 0;
}