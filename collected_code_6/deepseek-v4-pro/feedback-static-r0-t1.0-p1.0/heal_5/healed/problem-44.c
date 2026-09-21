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

    size_t i = 0;
    while (word[i] != '\0') {
        if (str[i] == '\0' || tolower((unsigned char)str[i]) != tolower((unsigned char)word[i])) {
            return false;
        }
        i++;
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

    volatile bool null_test1 = match_word_at_beginning(NULL, "test");
    volatile bool null_test2 = match_word_at_beginning("test", NULL);
    volatile bool null_test3 = match_word_at_beginning(NULL, NULL);
    
    if (!null_test1 && !null_test2 && !null_test3) {
        printf("NULL tests: false false false\n");
    }

    bool empty_test = match_word_at_beginning("test", "");
    printf("Empty word test: %s\n", empty_test ? "true" : "false");

    return 0;
}