#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    const char *test_words[] = {"hello", "world!", "C", "programming", NULL};
    
    for (size_t i = 0; test_words[i] != NULL; ++i) {
        bool result = is_word_length_odd(test_words[i]);
        printf("Word: %s, Odd length: %s\n", test_words[i], result ? "true" : "false");
    }
    
    return 0;
}