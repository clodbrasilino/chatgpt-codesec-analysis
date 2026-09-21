#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool matches_z_middle(const char *word) {
    if (word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    if (len < 3) {
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
        if (matches_z_middle(test_words[i])) {
            printf("MATCH: %s\n", test_words[i]);
        } else {
            printf("NO MATCH: %s\n", test_words[i]);
        }
    }

    return 0;
}