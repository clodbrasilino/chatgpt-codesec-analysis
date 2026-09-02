#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_word_at_beginning(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    size_t word_len = strlen(word);
    if (word_len == 0) {
        return false;
    }

    if (strncmp(str, word, word_len) != 0) {
        return false;
    }

    if (str[word_len] != '\0' && !isspace((unsigned char)str[word_len]) && 
        str[word_len] != '.' && str[word_len] != ',' && str[word_len] != ';' && 
        str[word_len] != ':' && str[word_len] != '!' && str[word_len] != '?' && 
        str[word_len] != '-' && str[word_len] != '_') {
        return false;
    }

    return true;
}

int main(void) {
    const char *test1 = "hello world";
    const char *test2 = "helloworld";
    const char *test3 = "hello, everyone";
    const char *test4 = "hello";
    const char *test5 = "he";
    
    if (match_word_at_beginning(test1, "hello")) {
        printf("Match found in '%s'\n", test1);
    } else {
        printf("No match in '%s'\n", test1);
    }
    
    if (match_word_at_beginning(test2, "hello")) {
        printf("Match found in '%s'\n", test2);
    } else {
        printf("No match in '%s'\n", test2);
    }
    
    if (match_word_at_beginning(test3, "hello")) {
        printf("Match found in '%s'\n", test3);
    } else {
        printf("No match in '%s'\n", test3);
    }
    
    if (match_word_at_beginning(test4, "hello")) {
        printf("Match found in '%s'\n", test4);
    } else {
        printf("No match in '%s'\n", test4);
    }
    
    if (match_word_at_beginning(test5, "hello")) {
        printf("Match found in '%s'\n", test5);
    } else {
        printf("No match in '%s'\n", test5);
    }
    
    /* Possible weaknesses found:
     *  Condition 'match_word_at_beginning(NULL,"hello")' is always false
     *  Condition 'match_word_at_beginning(NULL,"hello")' is always false [knownConditionTrueFalse]
     *  Calling function 'match_word_at_beginning' returns 0
     */
    if (match_word_at_beginning(NULL, "hello")) {
        printf("Match found in NULL\n");
    } else {
        printf("No match in NULL\n");
    }
    
    if (match_word_at_beginning("hello", NULL)) {
        printf("Match found with NULL word\n");
    } else {
        printf("No match with NULL word\n");
    }
    
    return 0;
}