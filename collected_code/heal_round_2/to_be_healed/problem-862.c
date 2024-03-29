#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_WORDS 100

typedef struct {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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

        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (!found && strlen(token) < MAX_SIZE && wordList.size < MAX_WORDS) {
            Word newWord;
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(newWord.word, token, MAX_SIZE);
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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