#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word, size_t max_len) {
    size_t length = strnlen(word, max_len);
    return length % 2 != 0;
}

int main() {
    const char *word = "example";
    size_t max_len = 8;
    if (is_odd_length(word, max_len)) {
        printf("The word has an odd length.\n");
    } else {
        printf("The word has an even length.\n");
    }
    return 0;
}