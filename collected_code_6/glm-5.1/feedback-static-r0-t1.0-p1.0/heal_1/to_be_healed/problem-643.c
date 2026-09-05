#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_z(const char *word) {
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'word==NULL' is redundant or there is possible null pointer dereference: word. [nullPointerRedundantCheck]
     */
    size_t len = strlen(word);
    /* Possible weaknesses found:
     *  Assuming that condition 'word==NULL' is not redundant
     */
    if (word == NULL) {
        return false;
    }
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