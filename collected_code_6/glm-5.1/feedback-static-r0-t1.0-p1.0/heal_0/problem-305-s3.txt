#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool match_p_words(const char *word1, const char *word2) {
    if (word1 == NULL || word2 == NULL) {
        return false;
    }

    size_t len1 = strlen(word1);
    size_t len2 = strlen(word2);

    if (len1 == 0 || len2 == 0) {
        return false;
    }

    if (word1[0] != 'p' || word2[0] != 'p') {
        return false;
    }

    return strcmp(word1, word2) == 0;
}

int main(void) {
    const char *word_list[] = {
        "pear",
        "peach",
        "apple",
        "plum",
        "p",
        "",
        "banana"
    };

    size_t list_size = sizeof(word_list) / sizeof(word_list[0]);
    bool found = false;

    for (size_t i = 0; i < list_size && !found; ++i) {
        for (size_t j = i + 1; j < list_size && !found; ++j) {
            if (match_p_words(word_list[i], word_list[j])) {
                found = true;
            }
        }
    }

    if (found) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}