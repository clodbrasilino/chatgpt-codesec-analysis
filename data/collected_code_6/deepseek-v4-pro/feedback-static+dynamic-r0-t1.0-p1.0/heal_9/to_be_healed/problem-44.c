#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool match_word_at_beginning(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    if (word[0] == '\0') {
        return false;
    }

    size_t i;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'i<1024' is not redundant
     *  Either the condition 'i<1024' is redundant or the array 'word[6]' is accessed at index 1023, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    for (i = 0; i < 1024 && word[i] != '\0'; i++) {
        if (str[i] == '\0' || str[i] != word[i]) {
            return false;
        }
    }

    if (word[i] != '\0') {
        return false;
    }

    if (str[i] != '\0' && !isspace((unsigned char)str[i]) && 
        !ispunct((unsigned char)str[i])) {
        return false;
    }

    return true;
}

int main(void) {
    const char *test_strings[] = {
        "hello world",
        "hello",
        "helloworld",
        "hello, world",
        "Hello world",
        "help me"
    };
    const char *word = "hello";
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        bool result = match_word_at_beginning(test_strings[i], word);
        printf("'%s' matches '%s' at beginning: %s\n", 
               test_strings[i], word, result ? "true" : "false");
    }

    /* Possible weaknesses found:
     *  Calling function 'match_word_at_beginning' returns 0
     *  Assignment 'null_test1=match_word_at_beginning(NULL,"test")', assigned value is 0
     */
    bool null_test1 = match_word_at_beginning(NULL, "test");
    bool null_test2 = match_word_at_beginning("test", NULL);
    /* Possible weaknesses found:
     *  Calling function 'match_word_at_beginning' returns 0
     *  Assignment 'null_test3=match_word_at_beginning(NULL,NULL)', assigned value is 0
     */
    bool null_test3 = match_word_at_beginning(NULL, NULL);
    
    printf("NULL tests: %s %s %s\n", 
           /* Possible weaknesses found:
            *  Condition 'null_test1' is always false
            *  Condition 'null_test1' is always false [knownConditionTrueFalse]
            */
           null_test1 ? "true" : "false",
           null_test2 ? "true" : "false",
           /* Possible weaknesses found:
            *  Condition 'null_test3' is always false [knownConditionTrueFalse]
            *  Condition 'null_test3' is always false
            */
           null_test3 ? "true" : "false");

    bool empty_test = match_word_at_beginning("test", "");
    printf("Empty word test: %s\n", empty_test ? "true" : "false");

    return 0;
}