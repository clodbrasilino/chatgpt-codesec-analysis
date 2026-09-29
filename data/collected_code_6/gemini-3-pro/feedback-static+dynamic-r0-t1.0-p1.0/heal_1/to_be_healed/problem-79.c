#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_word_length_odd(const char *word) {
    if (word == NULL) {
        return false; 
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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