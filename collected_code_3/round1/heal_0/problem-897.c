#include <stdio.h>
#include <string.h>

int checkWord(char* sentence, char* word) {
    char* p;

    p = strstr(sentence, word);

    if (p) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char sentence[1000], word[100];
    printf("Enter the sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    printf("Enter the word to be searched: ");
    fgets(word, sizeof(word), stdin);

    // Removing newline character from both strings
    sentence[strcspn(sentence, "\n")] = 0;
    word[strcspn(word, "\n")] = 0;

    if (checkWord(sentence, word)) {
        printf("Word found!\n");
    } else {
        printf("Word not found!\n");
    }

    return 0;
}