#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
    str[j] = '\0'; // Handle non-null terminated strings
}

WordList findMostCommonWords(char *text, int n) {
    WordList wordList = {{0}, 0};
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

        if (!found && strlen(token) < MAX_SIZE && wordList.size < MAX_WORDS) {
            Word newWord;
            strncpy(newWord.word, token, MAX_SIZE-1);
            newWord.word[MAX_SIZE-1] = '\0'; // Null terminate strncpy
            newWord.count = 1;
            wordList.words[wordList.size] = newWord;
            wordList.size++;
        }
        token = strtok(NULL, " ");
    }

    WordList commonWords = {{0}, n > wordList.size ? wordList.size : n};

    for (int i = 0; i < wordList.size; i++) {
        for (int j = i + 1; j < wordList.size; j++) {
            if (wordList.words[i].count < wordList.words[j].count) {
                Word temp = wordList.words[i];
                wordList.words[i] = wordList.words[j];
                wordList.words[j] = temp;
            }
        }
    }

    for (int i = 0; i < commonWords.size; i++) {
        commonWords.words[i] = wordList.words[i];
    }

    return commonWords;
}

int main() {
    char text[MAX_SIZE];
    int n;

    printf("Enter the text: ");
    if(!fgets(text, sizeof(text), stdin)) {
        printf("Error Reading text!\n");
        return 1;
    }

    printf("Enter the value of n: ");
    if(scanf("%d", &n)!=1) {
        printf("Invalid Input!\n");
        return 1;
    }

    WordList commonWords = findMostCommonWords(text, n);

    printf("Most common words:\n");
    for (int i = 0; i < commonWords.size; i++) {
        printf("%s (%d occurrences)\n", commonWords.words[i].word, commonWords.words[i].count);
    }

    return 0;
}