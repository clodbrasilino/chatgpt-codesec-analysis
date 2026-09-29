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

    for (i = 0; i < MAX_SIZE; i++) {
        if (str[i] == '\0') {
            break;
        }

        if (isalpha(str[i]) || str[i] == ' ') {
            str[j++] = tolower((unsigned char)str[i]);
        }
    }
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

        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (!found && strlen(token) < MAX_SIZE && wordList.size < MAX_WORDS) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(wordList.words[wordList.size].word, token, MAX_SIZE-1);
            wordList.words[wordList.size].word[MAX_SIZE-1] = '\0';
            wordList.words[wordList.size].count = 1;
            wordList.size++;
        }

        token = strtok(NULL , " ");
    }

    return wordList;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char text[MAX_SIZE];
    int n;

    printf("Enter the text: ");
    fgets(text, sizeof text, stdin);

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