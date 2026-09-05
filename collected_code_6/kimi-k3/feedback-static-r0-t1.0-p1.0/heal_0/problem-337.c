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
    
    if (word_len == 0 || str_len < word_len) {
        return false;
    }
    
    size_t end_pos = str_len;
    while (end_pos > 0 && ispunct((unsigned char)str[end_pos - 1])) {
        end_pos--;
    }
    
    if (end_pos < word_len) {
        return false;
    }
    
    size_t start_pos = end_pos - word_len;
    
    if (strncmp(str + start_pos, word, word_len) != 0) {
        return false;
    }
    
    if (start_pos > 0 && !isspace((unsigned char)str[start_pos - 1]) && 
        !ispunct((unsigned char)str[start_pos - 1])) {
        return false;
    }
    
    return true;
}

int main(void) {
    const char *test1 = "Hello world";
    const char *test2 = "Hello world!";
    const char *test3 = "Hello world...";
    const char *test4 = "Hello world?";
    const char *test5 = "world";
    const char *test6 = "Hello world,";
    const char *test7 = "Hello worldwide";
    const char *word = "world";
    
    printf("Test 1: %s\n", match_word_at_end(test1, word) ? "Match" : "No match");
    printf("Test 2: %s\n", match_word_at_end(test2, word) ? "Match" : "No match");
    printf("Test 3: %s\n", match_word_at_end(test3, word) ? "Match" : "No match");
    printf("Test 4: %s\n", match_word_at_end(test4, word) ? "Match" : "No match");
    printf("Test 5: %s\n", match_word_at_end(test5, word) ? "Match" : "No match");
    printf("Test 6: %s\n", match_word_at_end(test6, word) ? "Match" : "No match");
    printf("Test 7: %s\n", match_word_at_end(test7, word) ? "Match" : "No match");
    
    return 0;
}