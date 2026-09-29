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

typedef enum {
    LENGTH_EVEN,
    LENGTH_ODD,
    LENGTH_INVALID
} LengthStatus;

LengthStatus check_word_length(const char *word) {
    if (word == NULL) {
        return LENGTH_INVALID;
    }
    size_t len = strlen(word);
    return (len % 2 == 0) ? LENGTH_EVEN : LENGTH_ODD;
}

int main(int argc, char *argv[]) {
    const char *test_words[] = {
        "hello",
        "world!",
        "even",
        "",
        NULL
    };
    
    size_t num_words = sizeof(test_words) / sizeof(test_words[0]);

    for (size_t i = 0; i < num_words; i++) {
        LengthStatus status = check_word_length(test_words[i]);
        if (status == LENGTH_INVALID) {
            printf("NULL is invalid\n");
        } else if (status == LENGTH_EVEN) {
            printf("%s is even\n", test_words[i]);
        } else {
            printf("%s is odd\n", test_words[i]);
        }
    }

    return 0;
}