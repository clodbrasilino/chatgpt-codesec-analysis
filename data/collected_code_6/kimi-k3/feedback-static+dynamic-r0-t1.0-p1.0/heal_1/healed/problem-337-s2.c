#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool match_word_at_end(const char *str, size_t str_size, const char *word, size_t word_size) {
    if (str == NULL || word == NULL) {
        return false;
    }
    
    size_t str_len = 0;
    bool str_terminated = false;
    for (size_t i = 0; i < str_size; i++) {
        if (str[i] == '\0') {
            str_len = i;
            str_terminated = true;
            break;
        }
    }
    if (!str_terminated) {
        return false;
    }
    
    size_t word_len = 0;
    bool word_terminated = false;
    for (size_t i = 0; i < word_size; i++) {
        if (word[i] == '\0') {
            word_len = i;
            word_terminated = true;
            break;
        }
    }
    if (!word_terminated) {
        return false;
    }
    
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
        bool result = match_word_at_end(test_strings[i], strlen(test_strings[i]) + 1, word, strlen(word) + 1);
        printf("String: \"%s\" -> %s\n", test_strings[i], result ? "Match" : "No match");
    }
    
    return 0;
}