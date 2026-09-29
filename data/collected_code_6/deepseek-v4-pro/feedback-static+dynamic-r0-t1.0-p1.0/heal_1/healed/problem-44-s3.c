#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int is_word_delimiter(const char *str, size_t pos) {
    return str[pos] == '\0' || isspace((unsigned char)str[pos]) ||
           str[pos] == '.' || str[pos] == ',' || str[pos] == ';' ||
           str[pos] == ':' || str[pos] == '!' || str[pos] == '?';
}

int match_word(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return 0;
    }
    
    size_t word_len = 0;
    while (word[word_len] != '\0') {
        word_len++;
    }
    
    if (word_len == 0) {
        return 0;
    }
    
    size_t i = 0;
    while (i < word_len && str[i] != '\0') {
        if (str[i] != word[i]) {
            return 0;
        }
        i++;
    }
    
    if (i < word_len) {
        return 0;
    }
    
    if (!is_word_delimiter(str, word_len)) {
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