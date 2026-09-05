#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    
    for (int i = 0; i < 4; i++) {
        bool result = is_length_even(test_words[i]);
        if (result) {
            printf("%s is even\n", test_words[i]);
        } else {
            printf("%s is odd\n", test_words[i]);
        }
    }

    /* Possible weaknesses found:
     *  Condition 'is_length_even(NULL)' is always false
     *  Calling function 'is_length_even' returns 0
     *  Condition 'is_length_even(NULL)' is always false [knownConditionTrueFalse]
     */
    if (is_length_even(NULL)) {
        printf("NULL is even\n");
    } else {
        printf("NULL is odd\n");
    }

    return 0;
}