#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000
#define MAX_WORDS 100

typedef struct {
    char word[MAX_SIZE];
    int count;
} Word;

typedef struct {
    Word words[MAX_WORDS];
    int size;
} WordList;

void removeNonLetters(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i]) || str[i] == ' ') {
            str[j++] = tolower(str[i]);
        }
    }
    str[j] = '\0';
}

WordList findMostCommonWords(char *text, int n) {
    WordList wordList;
    wordList.size = 0;

    removeNonLetters(text);

    char *token = strtok(text, " ");

    while (token != NULL) {
        int i, found = 0;

        for (i = 0; i < wordList.size; i++) {
            if (strcmp(wordList.words[i].word, token) == 0) {
                wordList.words[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            Word newWord;
            strcpy(newWord.word, token);
            newWord.count = 1;
            wordList.words[wordList.size] = newWord;
            wordList.size++;
        }

        token = strtok(NULL, " ");
    }

    for (int i = 0; i < wordList.size; i++) {
        for (int j = i + 1; j < wordList.size; j++) {
            if (wordList.words[i].count < wordList.words[j].count) {
                Word temp = wordList.words[i];
                wordList.words[i] = wordList.words[j];
                wordList.words[j] = temp;
            }
        }
    }

    WordList commonWords;
    commonWords.size = n;

    if (n > wordList.size) {
        n = wordList.size;
    }

    for (int i = 0; i < n; i++) {
        commonWords.words[i] = wordList.words[i];
    }

    return commonWords;
}

int main() {
    char text[MAX_SIZE];
    int n;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the value of n: ");
    scanf("%d", &n);

    WordList commonWords = findMostCommonWords(text, n);

    printf("Most common words:\n");
    for (int i = 0; i < commonWords.size; i++) {
        printf("%s (%d occurrences)\n", commonWords.words[i].word, commonWords.words[i].count);
    }

    return 0;
}