#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_word_length_even(const char *word) {
    if (word == NULL) {
        return false;
    }
    
    size_t length = 0;
    const char *ptr = word;
    while (length < 1000 && *ptr != '\0') {
        length++;
        ptr++;
    }
    
    if (*ptr != '\0') {
        return false;
    }
    
    return (length % 2) == 0;
}

int main(void) {
    const char *test_words[] = {
        "hello",
        "world",
        "even",
        "odd",
        "a",
        "",
        NULL
    };

    for (int i = 0; test_words[i] != NULL; i++) {
        if (is_word_length_even(test_words[i])) {
            printf("\"%s\" has even length\n", test_words[i]);
        } else {
            printf("\"%s\" has odd length\n", test_words[i]);
        }
    }

    return 0;
}