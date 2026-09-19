#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *word == '\0') {
        return false;
    }

    size_t sentence_len = strlen(sentence);
    size_t word_len = strlen(word);
    size_t i = 0;

    while (i < sentence_len) {
        while (i < sentence_len && !isalnum((unsigned char)sentence[i])) {
            i++;
        }

        if (i >= sentence_len) {
            break;
        }

        size_t start = i;
        while (i < sentence_len && isalnum((unsigned char)sentence[i])) {
            i++;
        }
        size_t token_len = i - start;

        if (token_len == word_len) {
            bool match = true;
            for (size_t j = 0; j < word_len; j++) {
                if (tolower((unsigned char)sentence[start + j]) != tolower((unsigned char)word[j])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    const char sentence[] = "The quick brown fox jumps over the lazy dog";
    const char word[] = "fox";

    if (word_present(sentence, word)) {
        printf("The word '%s' is present in the sentence.\n", word);
    } else {
        printf("The word '%s' is not present in the sentence.\n", word);
    }

    return 0;
}