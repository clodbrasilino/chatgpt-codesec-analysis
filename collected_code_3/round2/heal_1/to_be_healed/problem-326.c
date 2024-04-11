#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

struct WordCount {
    char word[MAX_WORD_LENGTH];
    int count;
};

char* getMostFrequentWord(char* strings[], int n) {
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

    /* Possible weaknesses found:
     *  function returns address of local variable [-Wreturn-local-addr]
     */
    return wc[maxCountIndex].word;
}

int main() {
    int n;
    printf("Enter the number of words: ");
    scanf("%d", &n);

    char** strings = (char**)malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'strings' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        strings[i] = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
        printf("Enter word %d: ", i + 1);
        scanf("%s", strings[i]);
    }

    char* mostFrequentWord = getMostFrequentWord(strings, n);
    printf("The most frequent word is: %s\n", mostFrequentWord);

    for(int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}