#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_word_length_odd(const char *word) {
    if (word == NULL) {
        return false; 
    }
    size_t length = strlen(word);
    return (length % 2) != 0;
}

int main(void) {
    const char *word1 = "hello";
    const char *word2 = "world!";
    
    if (is_word_length_odd(word1)) {
        printf("%s has odd length.\n", word1);
    } else {
        printf("%s has even length.\n", word1);
    }
    
    if (is_word_length_odd(word2)) {
        printf("%s has odd length.\n", word2);
    } else {
        printf("%s has even length.\n", word2);
    }
    
    return 0;
}