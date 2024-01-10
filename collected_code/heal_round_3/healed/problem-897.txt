#include <stdio.h>
#include <string.h>

#define SENTENCE_SIZE 101
#define WORD_SIZE 21

int isWordPresent(const char *sentence, const char *word) {
    size_t sentenceLength = strnlen(sentence, SENTENCE_SIZE);
    size_t wordLength = strnlen(word, WORD_SIZE);

    for (size_t i = 0; i <= sentenceLength - wordLength; i++) {
        size_t j;
        for (j = 0; j < wordLength; j++) {
            if (sentence[i + j] != word[j]) {
                break;
            }
        }
        if (j == wordLength) {
            return 1;
        }
    }
    return 0;
}

int main() {
    
    char sentence[SENTENCE_SIZE] = {0};
    char word[WORD_SIZE] = {0};

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = 0;

    printf("Enter a word: ");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = 0;

    if (isWordPresent(sentence, word)) {
        printf("Word is present in the sentence");
    } else {
        printf("Word is not present in the sentence");
    }

    return 0;
}