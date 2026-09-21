#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_z(const char *word, size_t len) {
    if (word == NULL) {
        return false;
    }

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
        size_t len = strnlen(test_words[i], 1024);
        if (len == 1024) {
            continue;
        }
        bool result = match_z(test_words[i], len);
        if (result) {
            printf("%s: true\n", test_words[i]);
        } else {
            printf("%s: false\n", test_words[i]);
        }
    }

    return 0;
}