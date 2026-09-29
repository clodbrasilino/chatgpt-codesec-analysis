#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word) {
    if (word == NULL) {
        return false;
    }
    size_t len = strlen(word);
    return len % 2 != 0;
}

int main(void) {
    const char *test_words[] = {"hello", "world", "C", "programming", NULL};
    size_t count = sizeof(test_words) / sizeof(test_words[0]);
    
    for (size_t i = 0; i < count; i++) {
        if (test_words[i] != NULL) {
            if (is_odd_length(test_words[i])) {
                printf("%s has odd length\n", test_words[i]);
            } else {
                printf("%s has even length\n", test_words[i]);
            }
        }
    }
    
    return 0;
}