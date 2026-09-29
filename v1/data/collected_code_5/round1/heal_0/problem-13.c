#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} Word;

Word *dictionary[MAX_WORDS];

int dictionarySize = 0;

void incrementWordCount(char *word) {
    for(int i = 0; i < dictionarySize; i++) {
        if(strcmp(dictionary[i]->word, word) == 0) {
            dictionary[i]->count++;
            return;
        }
    }

    Word *newWord = (Word *) malloc(sizeof(Word));
    strcpy(newWord->word, word);
    newWord->count = 1;

    dictionary[dictionarySize++] = newWord;
}

void printMostCommonWords() {
    int maxCount = 0;
    
    for(int i = 0; i < dictionarySize; i++) {
        if(dictionary[i]->count > maxCount)
            maxCount = dictionary[i]->count;
    }
    
    for(int i = 0; i < dictionarySize; i++) {
        if(dictionary[i]->count == maxCount)
            printf("Most common word: %s, Count: %d\n", dictionary[i]->word, dictionary[i]->count);
    }
    
    for(int i = 0; i<dictionarySize; i++) {
        free(dictionary[i]);
    }
}

int main() {
    const char *text = "This is a simple, simple and a very simple word counting program in c.";
    char word[MAX_WORD_LENGTH];
    int count = 0;

    for(int i = 0; i < strlen(text); i++) {
        if(text[i] != ' ' && text[i] != '.' && text[i] != ',') {
            word[count++] = text[i];
        } else {
            word[count++] = '\0';
            incrementWordCount(word);
            count = 0;
        }
    }

    printMostCommonWords();

    return 0;
}