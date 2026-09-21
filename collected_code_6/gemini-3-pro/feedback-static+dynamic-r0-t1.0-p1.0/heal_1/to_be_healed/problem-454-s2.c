#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool matches_z_word(const char *word) {
    if (word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    if (len == 0) {
        return false;
    }

    bool has_z = false;
    for (size_t i = 0; i < len; ++i) {
        if (!isalpha((unsigned char)word[i])) {
            return false;
        }
        if (word[i] == 'z' || word[i] == 'Z') {
            has_z = true;
        }
    }

    return has_z;
}

int main(void) {
    const char *test_words[] = {
        "apple",
        "zebra",
        "hello",
        "buzz",
        "pizza",
        "z123",
        NULL
    };

    for (size_t i = 0; test_words[i] != NULL; ++i) {
        if (matches_z_word(test_words[i])) {
            printf("%s\n", test_words[i]);
        }
    }

    return 0;
}