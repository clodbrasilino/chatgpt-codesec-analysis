#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_z(const char *word) {
    if (word == NULL) {
        return false;
    }
    size_t len = strlen(word);
    if (len < 3) {
        return false;
    }
    for (size_t i = 1; i < len - 1; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }
    return false;
}

int main(void) {
    const char *test_words[] = {
        "zebra",
        "zoo",
        "blizzard",
        "pizza",
        "piz",
        "az",
        "za",
        "z",
        "zz",
        "amazon",
        "buzz",
        "Zephyr",
        "aZure"
    };
    size_t count = sizeof(test_words) / sizeof(test_words[0]);
    for (size_t i = 0; i < count; i++) {
        printf("%s: %s\n", test_words[i], match_z(test_words[i]) ? "true" : "false");
    }
    return 0;
}