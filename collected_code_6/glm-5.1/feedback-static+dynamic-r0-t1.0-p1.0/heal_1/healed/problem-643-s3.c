#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool matches_z_middle(const char *word, size_t len) {
    if (word == NULL || len < 3) {
        return false;
    }

    bool has_z = false;

    for (size_t i = 0; i < len; ++i) {
        if (word[i] == 'z' || word[i] == 'Z') {
            if (i == 0 || i == len - 1) {
                return false;
            }
            has_z = true;
        }
    }

    return has_z;
}

int main(void) {
    const char *test_words[] = {
        "zebra",
        "zoo",
        "pizza",
        "blizzard",
        "buzz",
        "az",
        "za",
        "z",
        "aztec",
        "puzzle",
        NULL
    };

    for (size_t i = 0; test_words[i] != NULL; ++i) {
        size_t len = 0;
        while (test_words[i][len] != '\0') {
            len++;
        }
        if (matches_z_middle(test_words[i], len)) {
            printf("MATCH: %s\n", test_words[i]);
        } else {
            printf("NO MATCH: %s\n", test_words[i]);
        }
    }

    return 0;
}