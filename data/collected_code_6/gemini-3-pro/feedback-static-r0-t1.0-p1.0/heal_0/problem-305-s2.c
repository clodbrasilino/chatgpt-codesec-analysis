#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_words(const char *word1, const char *word2) {
    if (word1 == NULL || word2 == NULL) {
        return 0;
    }

    if (word1[0] != 'p' || word2[0] != 'p') {
        return 0;
    }

    if (strcmp(word1, word2) == 0) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *words[] = {"apple", "pear", "peach", "plum", "pear"};
    size_t num_words = sizeof(words) / sizeof(words[0]);

    for (size_t i = 0; i < num_words; i++) {
        for (size_t j = i + 1; j < num_words; j++) {
            if (match_words(words[i], words[j])) {
                printf("Match found: %s and %s\n", words[i], words[j]);
            }
        }
    }

    return 0;
}