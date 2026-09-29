#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_SIZE 100
#define MAX_WORDS 1000

struct WordCount {
    char word[MAX_WORD_SIZE];
    int count;
};

char* getMostFrequentWord(char* strings[], int size) {
    struct WordCount wordCounts[MAX_WORDS];
    int totalWords = 0;

    for(int i = 0; i < size; i++) {
        char* token = strtok(strings[i], " ");
        while(token != NULL) {
            int found = 0;
            for(int j = 0; j < totalWords; j++) {
                if(strcmp(wordCounts[j].word, token) == 0) {
                    wordCounts[j].count++;
                    found = 1;
                    break;
                }
            }
            if(!found) {
                strcpy(wordCounts[totalWords].word, token);
                wordCounts[totalWords].count = 1;
                totalWords++;
            }
            token = strtok(NULL, " ");
        }
    }

    int maxCountIndex = 0;
    for(int i = 1; i < totalWords; i++) {
        if(wordCounts[i].count > wordCounts[maxCountIndex].count) {
            maxCountIndex = i;
        }
    }

    /* Possible weaknesses found:
     *  function returns address of local variable [-Wreturn-local-addr]
     */
    return wordCounts[maxCountIndex].word;
}

int main() {
    char* strings[] = {"Hello world", "world is beautiful", "Hello everyone"};
    int size = sizeof(strings) / sizeof(strings[0]);

    char* mostFrequentWord = getMostFrequentWord(strings, size);
    printf("Most frequent word: %s\n", mostFrequentWord);

    return 0;
}