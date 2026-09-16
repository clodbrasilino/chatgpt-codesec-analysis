#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool contains_z(const char *word) {
    if (word == NULL) {
        return false;
    }

    for (size_t i = 0; word[i] != '\0'; i++) {
        if (tolower((unsigned char)word[i]) == 'z') {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *test_words[] = {
        "zero",
        "apple",
        "zebra",
        "Zigzag",
        "banana",
        NULL
    };

    for (size_t i = 0; test_words[i] != NULL; i++) {
        if (contains_z(test_words[i])) {
            printf("\"%s\" contains 'z'\n", test_words[i]);
        } else {
            printf("\"%s\" does not contain 'z'\n", test_words[i]);
        }
    }

    return 0;
}