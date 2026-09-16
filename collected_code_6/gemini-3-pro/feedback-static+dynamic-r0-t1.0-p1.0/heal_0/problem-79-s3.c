#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_word_length_odd(const char *word) {
    if (word == NULL) {
        return false;
    }
    
    size_t length = strlen(word);
    return (length % 2) != 0;
}

int main(void) {
    const char *test_words[] = {"hello", "world!", "C", "programming", NULL};
    
    for (size_t i = 0; test_words[i] != NULL; ++i) {
        bool result = is_word_length_odd(test_words[i]);
        printf("Word: %s, Odd length: %s\n", test_words[i], result ? "true" : "false");
    }
    
    return 0;
}