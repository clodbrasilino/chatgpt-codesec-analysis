#include <stdio.h>
#include <string.h>

int is_length_even(const char *word) {
    if (word == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(word);
    
    if (length % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    const char *test_words[] = {"hello", "word", "C", "programming", NULL};
    
    for (int i = 0; test_words[i] != NULL; i++) {
        if (is_length_even(test_words[i])) {
            printf("The length of '%s' is even.\n", test_words[i]);
        } else {
            printf("The length of '%s' is odd.\n", test_words[i]);
        }
    }
    
    return 0;
}