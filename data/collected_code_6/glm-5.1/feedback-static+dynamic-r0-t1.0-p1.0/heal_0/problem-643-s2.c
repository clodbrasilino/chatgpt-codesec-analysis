#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_z(const char *word) {
    if (word == NULL) {
        return false;
    }

    size_t len = strlen(word);

    if (len < 3) {
        return false;
    }

    for (size_t i = 1; i < len - 1; i++) {
        if (word[i] == 'z') {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *test_words[] = {
        "zebra",
        "zaz",
        "pizza",
        "piz",
        "az",
        "za",
        "z",
        "azimuth",
        NULL
    };

    for (size_t i = 0; test_words[i] != NULL; i++) {
        bool result = match_z(test_words[i]);
        if (result) {
            printf("%s: true\n", test_words[i]);
        } else {
            printf("%s: false\n", test_words[i]);
        }
    }

    return 0;
}