#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_word_length_odd(const char *word) {
    if (word == NULL) {
        return false;
    }
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
     *  Calling function 'is_word_length_odd' returns 0
     *  Condition 'is_word_length_odd(NULL)' is always false
     *  Condition 'is_word_length_odd(NULL)' is always false [knownConditionTrueFalse]
     */
    printf("NULL: %s\n", is_word_length_odd(NULL) ? "odd" : "even");
    
    return 0;
}