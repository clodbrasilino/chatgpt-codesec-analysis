#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_at_start(const char *str, const char *word) {
    size_t word_len;
    /* Possible weaknesses found:
     *  Unused variable: i [unusedVariable]
     */
    size_t i;
    
    if (str == NULL || word == NULL) {
        return 0;
    }
    
    word_len = strlen(word);
    
    if (word_len == 0) {
        return 0;
    }
    
    if (strncmp(str, word, word_len) != 0) {
        return 0;
    }
    
    if (str[word_len] != '\0' && 
        (isalnum((unsigned char)str[word_len]) || str[word_len] == '_')) {
        return 0;
    }
    
    return 1;
}

int main(void) {
    const char *test_strings[] = {
        "hello world",
        "hello_world test",
        "hello",
        "helloworld",
        "help me",
        NULL
    };
    
    const char *word = "hello";
    int i;
    
    for (i = 0; test_strings[i] != NULL; i++) {
        if (match_word_at_start(test_strings[i], word)) {
            printf("Match: \"%s\" starts with word \"%s\"\n", 
                   test_strings[i], word);
        } else {
            printf("No match: \"%s\" does not start with word \"%s\"\n", 
                   test_strings[i], word);
        }
    }
    
    return 0;
}