#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_word_in_sentence(const char *sentence, const char *word) {
    size_t sentence_len = strlen(sentence);
    size_t word_len = strlen(word);
    if (word_len > sentence_len) return false;

    for (size_t i = 0; i <= sentence_len - word_len; i++) {
        if (strncmp(sentence + i, word, word_len) == 0) {
            if (i == 0 || !isalpha(sentence[i - 1])) {
                if (i + word_len == sentence_len || !isalpha(sentence[i + word_len])) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    const char *sentence = "This is a test sentence to check if the word is present";
    const char *word = "test";

    if (is_word_in_sentence(sentence, word)) {
        printf("The word is present in the sentence.\n");
    } else {
        printf("The word is not present in the sentence.\n");
    }

    return 0;
}