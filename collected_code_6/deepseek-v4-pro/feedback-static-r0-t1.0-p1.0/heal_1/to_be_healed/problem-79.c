#include <stdio.h>
#include <string.h>

int is_word_length_odd(const char *word) {
    if (word == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(word);
    return length % 2 == 1;
}

int main(void) {
    const char *test_words[] = {"hello", "world", "C", "programming", "", NULL};
    
    for (int i = 0; test_words[i] != NULL; i++) {
        if (is_word_length_odd(test_words[i])) {
            printf("\"%s\" has odd length\n", test_words[i]);
        } else {
            printf("\"%s\" has even length\n", test_words[i]);
        }
    }
    
    return 0;
}