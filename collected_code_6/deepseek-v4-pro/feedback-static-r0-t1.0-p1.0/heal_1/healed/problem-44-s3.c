#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int match_word(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return 0;
    }
    
    size_t word_len = safe_strlen(word, 1024);
    if (word_len == 0 || word_len >= 1024) {
        return 0;
    }
    
    size_t str_len = safe_strlen(str, 4096);
    if (str_len < word_len) {
        return 0;
    }
    
    if (strncmp(str, word, word_len) != 0) {
        return 0;
    }
    
    if (str[word_len] != '\0' && !isspace((unsigned char)str[word_len]) && 
        str[word_len] != '.' && str[word_len] != ',' && str[word_len] != ';' &&
        str[word_len] != ':' && str[word_len] != '!' && str[word_len] != '?') {
        return 0;
    }
    
    return 1;
}

int main(void) {
    const char *text1 = "hello world";
    const char *text2 = "hello, world";
    const char *text3 = "hello!";
    const char *text4 = "helloworld";
    const char *text5 = "world hello";
    
    const char *word1 = "hello";
    const char *word2 = "world";
    const char *word3 = "";
    
    printf("%d\n", match_word(text1, word1));
    printf("%d\n", match_word(text2, word1));
    printf("%d\n", match_word(text3, word1));
    printf("%d\n", match_word(text4, word1));
    printf("%d\n", match_word(text5, word2));
    printf("%d\n", match_word(text1, word2));
    printf("%d\n", match_word(text1, word3));
    printf("%d\n", match_word(NULL, word1));
    printf("%d\n", match_word(text1, NULL));
    
    return 0;
}