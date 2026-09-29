#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} Word;

Word words[MAX_WORDS];
int wordCount = 0;

void addWord(char* word) {
    for(int i = 0; i < wordCount; i++) {
        if(strcmp(words[i].word, word) == 0) {
            words[i].count++;
            return;
        }
    }
    strcpy(words[wordCount].word, word);
    words[wordCount].count = 1;
    wordCount++;
}

int compare(const void* a, const void* b) {
    Word* wordA = (Word*) a;
    Word* wordB = (Word*) b;
    return wordB->count - wordA->count;
}

void printTopN(int n) {
    qsort(words, wordCount, sizeof(Word), compare);
    for(int i = 0; i < n && i < wordCount; i++) {
        printf("%s: %d\n", words[i].word, words[i].count);
    }
}

int main() {
    char text[] = "This is a test. This is only a test. Testing, one, two, three.";
    char* word = strtok(text, " .,!?");

    while(word != NULL) {
        addWord(word);
        word = strtok(NULL, " .,!?");
    }

    printTopN(3);

    return 0;
}