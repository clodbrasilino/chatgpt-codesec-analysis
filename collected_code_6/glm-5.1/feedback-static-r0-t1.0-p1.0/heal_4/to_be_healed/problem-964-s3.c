#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    LENGTH_RESULT_EVEN,
    LENGTH_RESULT_ODD,
    LENGTH_RESULT_INVALID
} LengthResult;

LengthResult is_length_even(const char *word) {
    if (word == NULL) {
        return LENGTH_RESULT_INVALID;
    }
    size_t len = strlen(word);
    return (len % 2) == 0 ? LENGTH_RESULT_EVEN : LENGTH_RESULT_ODD;
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
        LengthResult result = is_length_even(test_words[i]);
        if (result == LENGTH_RESULT_EVEN) {
            printf("%s is even\n", test_words[i]);
        } else {
            printf("%s is odd\n", test_words[i]);
        }
    }

    const char *null_word = NULL;
    /* Possible weaknesses found:
     *  Assignment 'null_result=is_length_even(null_word)', assigned value is 2
     *  Calling function 'is_length_even' returns 2
     */
    LengthResult null_result = is_length_even(null_word);
    /* Possible weaknesses found:
     *  Condition 'null_result==LENGTH_RESULT_INVALID' is always true [knownConditionTrueFalse]
     *  Condition 'null_result==LENGTH_RESULT_INVALID' is always true
     */
    if (null_result == LENGTH_RESULT_INVALID) {
        printf("NULL is invalid\n");
    } else if (null_result == LENGTH_RESULT_EVEN) {
        printf("NULL is even\n");
    } else if (null_result == LENGTH_RESULT_ODD) {
        printf("NULL is odd\n");
    }

    return 0;
}