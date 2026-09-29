#include <stdio.h>
#include <string.h>

int checkWordInSentence(char *sentence, char *word) {
    if(strstr(sentence, word) != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char sentence[100];
    char word[50];

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    printf("Enter a word to search: ");
    fgets(word, sizeof(word), stdin);

    // Removing the newline character from both strings
    sentence[strcspn(sentence, "\n")] = 0;
    word[strcspn(word, "\n")] = 0;

    if(checkWordInSentence(sentence, word)) {
        printf("The word '%s' is present in the sentence.\n", word);
    } else {
        printf("The word '%s' is not present in the sentence.\n", word);
    }

    return 0;
}