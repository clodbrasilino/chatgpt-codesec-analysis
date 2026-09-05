#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool is_length_even(const char *word) {
    if (word == NULL) {
        return false;
    }
    size_t len = strlen(word);
    return (len % 2) == 0;
}

int main(int argc, char *argv[]) {
    const char *test_words[] = {
        "hello",
        "world!",
        "even",
        "",
        NULL
    };
    
    for (int i = 0; test_words[i] != NULL; i++) {
        bool result = is_length_even(test_words[i]);
        if (result) {
            printf("%s is even\n", test_words[i]);
        } else {
            printf("%s is odd\n", test_words[i]);
        }
    }

    const char *null_word = NULL;
    /* Possible weaknesses found:
     *  Assignment 'null_result=is_length_even(null_word)', assigned value is 0
     *  Calling function 'is_length_even' returns 0
     */
    bool null_result = is_length_even(null_word);
    /* Possible weaknesses found:
     *  Condition 'null_result' is always false [knownConditionTrueFalse]
     *  Condition 'null_result' is always false
     */
    if (null_result) {
        printf("NULL is even\n");
    } else {
        printf("NULL is odd\n");
    }

    return 0;
}