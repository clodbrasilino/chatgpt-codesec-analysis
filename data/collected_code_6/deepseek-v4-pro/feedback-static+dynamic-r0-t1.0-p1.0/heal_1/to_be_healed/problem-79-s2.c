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
    const char *test_words[] = {"hello", "world", "C", "programming", NULL};
    
    for (int i = 0; test_words[i] != NULL; i++) {
        printf("%s: %s\n", test_words[i], 
               is_word_length_odd(test_words[i]) ? "odd" : "even");
    }
    
    /* Possible weaknesses found:
     *  Condition 'is_word_length_odd(NULL)' is always false
     *  Condition 'is_word_length_odd(NULL)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_word_length_odd' returns 0
     */
    if (is_word_length_odd(NULL)) {
        printf("NULL: odd\n");
    } else {
        printf("NULL: even\n");
    }
    
    return 0;
}