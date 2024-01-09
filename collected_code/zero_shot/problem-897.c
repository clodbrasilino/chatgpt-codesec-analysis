#include <stdio.h>
#include <string.h>

int isWordPresent(char sentence[], char word[]) {
    int sentenceLength = strlen(sentence);
    int wordLength = strlen(word);

    for (int i = 0; i <= sentenceLength - wordLength; i++) {
        int j;
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
    char sentence[100];
    char word[20];

    printf("Enter a sentence: ");
    gets(sentence);

    printf("Enter a word: ");
    gets(word);

    if (isWordPresent(sentence, word)) {
        printf("Word is present in the sentence");
    } else {
        printf("Word is not present in the sentence");
    }

    return 0;
}