#include <stdio.h>
#include <string.h>

int checkIfWordExists(char* sentence, char* word) {
    char* occurrence = strstr(sentence, word);

    if (occurrence != NULL) {
        return 1;
    }

    return 0;
}

int main() {
    char sentence[100];
    char word[100];

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    printf("Enter a word to search: ");
    fgets(word, sizeof(word), stdin);

    sentence[strlen(sentence) - 1] = '\0';
    word[strlen(word) - 1] = '\0';

    if (checkIfWordExists(sentence, word)) {
        printf("The word exists in the sentence.\n");
    }
    else {
        printf("The word does not exist in the sentence.\n");
    }

    return 0;
}