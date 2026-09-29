#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool match_p_words(const char *word1, const char *word2) {
    if (word1 == NULL || word2 == NULL) {
        return false;
    }
    if (word1[0] != 'p' || word2[0] != 'p') {
        return false;
    }
    return strcmp(word1, word2) == 0;
}

int main(void) {
    const char *words[] = {"apple", "pear", "peach", "plum", "piano", "grape"};
    size_t num_words = sizeof(words) / sizeof(words[0]);
    bool found = false;

    for (size_t i = 0; i < num_words; i++) {
        for (size_t j = i + 1; j < num_words; j++) {
            if (match_p_words(words[i], words[j])) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (found) {
        printf("Match found among 'p' words.\n");
    } else {
        printf("No match found among 'p' words.\n");
    }

    return 0;
}