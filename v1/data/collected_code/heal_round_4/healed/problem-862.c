#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 1001
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
    char temp[MAX_SIZE] = {0};

    for (i = 0; i < MAX_SIZE && str[i] != '\0'; i++) {
        if (isalpha(str[i]) || str[i] == ' ') {
            temp[j++] = tolower((unsigned char)str[i]);
        }
    }

    strncpy(str, temp, j);
    str[j] = '\0';
}

WordList findMostCommonWords(char *text) {
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
            strncpy(wordList.words[wordList.size].word, token, strlen(token));
            wordList.words[wordList.size].count = 1;
            wordList.size++;
        }

        token = strtok(NULL , " ");
    }

    return wordList;
}

int main() {
    char text[MAX_SIZE] = {0};
    int n = 0;

    printf("Enter the text: ");
    fgets(text, MAX_SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    WordList wordList = findMostCommonWords(text);
    WordList mostCommonWords;

    int howMany = n > wordList.size ? wordList.size : n;

    for (int i = 0; i < howMany; i++) {
        mostCommonWords.words[i] = wordList.words[i];
    }

    mostCommonWords.size = howMany;

    printf("Most common words:\n");

    for (int i = 0; i < mostCommonWords.size; i++) {
        printf("%s (%d occurrences)\n", mostCommonWords.words[i].word, mostCommonWords.words[i].count);
    }

    return 0;
}