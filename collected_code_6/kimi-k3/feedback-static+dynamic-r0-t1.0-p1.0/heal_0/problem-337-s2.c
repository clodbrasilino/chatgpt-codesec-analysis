#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool match_word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }
    
    size_t str_len = strlen(str);
    size_t word_len = strlen(word);
    
    if (word_len == 0) {
        return false;
    }
    
    size_t end = str_len;
    while (end > 0 && ispunct((unsigned char)str[end - 1])) {
        end--;
    }
    
    if (end < word_len) {
        return false;
    }
    
    size_t start = end - word_len;
    
    if (strncmp(str + start, word, word_len) != 0) {
        return false;
    }
    
    if (start > 0 && !isspace((unsigned char)str[start - 1]) && !ispunct((unsigned char)str[start - 1])) {
        return false;
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "Hello world",
        "Hello world!",
        "Hello world.",
        "Hello world!?",
        "Hello my world",
        "world",
        "world!",
        "Hello world, how are you",
        "The word is sword",
        "Hello world! "
    };
    
    const char *word = "world";
    
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
        bool result = match_word_at_end(test_strings[i], word);
        printf("String: \"%s\" -> %s\n", test_strings[i], result ? "Match" : "No match");
    }
    
    return 0;
}