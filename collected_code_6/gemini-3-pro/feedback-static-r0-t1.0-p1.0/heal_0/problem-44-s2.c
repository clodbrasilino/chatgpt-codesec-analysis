#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool match_word_at_beginning(const char *string, const char *word) {
    if (string == NULL || word == NULL) {
        return false;
    }

    size_t word_len = strlen(word);
    
    if (word_len == 0) {
        return true; 
    }
    
    if (strncmp(string, word, word_len) != 0) {
        return false;
    }

    char next_char = string[word_len];
    if (next_char == '\0' || next_char == ' ' || next_char == '\t' || next_char == '\n' || next_char == '\r') {
        return true;
    }

    return false;
}

int main(void) {
    const char *text1 = "Hello world";
    const char *word1 = "Hello";
    
    const char *text2 = "HelloWorld";
    const char *word2 = "Hello";
    
    const char *text3 = "Hi there";
    const char *word3 = "Hello";

    bool result1 = match_word_at_beginning(text1, word1);
    bool result2 = match_word_at_beginning(text2, word2);
    bool result3 = match_word_at_beginning(text3, word3);

    printf("Result 1: %d\n", result1);
    printf("Result 2: %d\n", result2);
    printf("Result 3: %d\n", result3);

    return 0;
}