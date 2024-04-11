#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

struct WordCount {
    char word[MAX_WORD_LENGTH];
    int count;
};

void getMostFrequentWord(char* strings[], int n, char* mostFrequentWord) {
    struct WordCount wc[MAX_WORDS];
    int wcSize = 0;

    for(int i = 0; i < n; i++) {
        char* word = strings[i];
        int j;
        for(j = 0; j < wcSize; j++) {
            if(strcmp(wc[j].word, word) == 0) {
                wc[j].count++;
                break;
            }
        }
        if(j == wcSize) {
            strcpy(wc[wcSize].word, word);
            wc[wcSize].count = 1;
            wcSize++;
        }
    }

    int maxCountIndex = 0;
    for(int i = 1; i < wcSize; i++) {
        if(wc[i].count > wc[maxCountIndex].count) {
            maxCountIndex = i;
        }
    }

    strcpy(mostFrequentWord, wc[maxCountIndex].word);
}

int main() {
    int n;
    printf("Enter the number of words: ");
    scanf("%d", &n);

    if(n < 0) {
        printf("Invalid number of words\n");
        return 1;
    }

    char** strings = (char**)malloc(n * sizeof(char*));
    if(strings == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    for(int i = 0; i < n; i++) {
        strings[i] = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
        if(strings[i] == NULL) {
            printf("Failed to allocate memory\n");
            for(int j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }
        printf("Enter word %d: ", i + 1);
        scanf("%s", strings[i]);
    }

    char mostFrequentWord[MAX_WORD_LENGTH];
    getMostFrequentWord(strings, n, mostFrequentWord);
    printf("The most frequent word is: %s\n", mostFrequentWord);

    for(int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}