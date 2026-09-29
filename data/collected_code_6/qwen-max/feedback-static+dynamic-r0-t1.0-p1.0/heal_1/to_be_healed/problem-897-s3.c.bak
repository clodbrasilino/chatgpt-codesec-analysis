#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_word_in_sentence(const char *sentence, const char *word) {
    size_t word_len = strlen(word);
    size_t sentence_len = strlen(sentence);

    if (word_len > sentence_len) {
        return false;
    }

    for (size_t i = 0; i <= sentence_len - word_len; ++i) {
        if (strncmp(&sentence[i], word, word_len) == 0) {
            /* Possible weaknesses found:
             *  Condition 'sentence[i+word_len]!='\0'' is always true [knownConditionTrueFalse]
             */
            if (i + word_len < sentence_len && (sentence[i + word_len] != ' ' && sentence[i + word_len] != '\t' && sentence[i + word_len] != '\n' && sentence[i + word_len] != '\0')) {
                continue;
            }
            if (i > 0 && (sentence[i - 1] != ' ' && sentence[i - 1] != '\t' && sentence[i - 1] != '\n')) {
                continue;
            }
            return true;
        }
    }
    return false;
}

int main() {
    const char *sentence = "This is a sample sentence with several words.";
    const char *word = "sample";
    bool found = is_word_in_sentence(sentence, word);
    if (found) {
        printf("The word '%s' is present in the sentence.\n", word);
    } else {
        printf("The word '%s' is not present in the sentence.\n", word);
    }
    return 0;
}