#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

struct Word {
    char str[MAX_WORD_LENGTH];
    int count;
};

void addWord(struct Word words[], int *n, char *word) {
    int i;
    for(i = 0; i < *n; i++) {
        if(strcmp(words[i].str, word) == 0) {
            words[i].count++;
            return;
        }
    }
    strcpy(words[*n].str, word);
    words[*n].count = 1;
    (*n)++;
}

char* mostFrequentWord(char *str) {
    struct Word words[MAX_WORDS];
    int n = 0, i, max;
    char *word, *delim = " ", *result;
    word = strtok(str, delim);
    while(word != NULL) {
        addWord(words, &n, word);
        word = strtok(NULL, delim);
    }
    max = 0;
    for(i = 1; i < n; i++) {
        if(words[i].count > words[max].count) {
            max = i;
        }
    }
    result = (char*)malloc(strlen(words[max].str) + 1);
    strcpy(result, words[max].str);
    return result;
}

int main() {
    char str[] = "apple banana apple orange banana apple";
    char *result = mostFrequentWord(str);
    printf("%s\n", result);
    free(result);
    return 0;
}