#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define DICTIONARY_SIZE 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;


WordCount* countWords(char* dictionary[], int size) {
    WordCount* wordCounts = malloc(sizeof(WordCount) * size);
    if(wordCounts == NULL){
        printf("Memory not allocated.\n");
        exit(0);
    }
    
    for(int i = 0; i < size; i++){
        int found = 0;
        for(int j = 0; j < i; j++){
            if(strcmp(dictionary[i], wordCounts[j].word) == 0){
                wordCounts[j].count++;
                found = 1;
                break;
            }   
        }
        
        if(found == 0){
            strcpy(wordCounts[i].word, dictionary[i]);
            wordCounts[i].count = 1;  
        }
    }

    return wordCounts;
}

int main() {
    char* dictionary[DICTIONARY_SIZE];
    for(int i = 0; i < DICTIONARY_SIZE; i++) {
        dictionary[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
        if(dictionary[i] == NULL){
            printf("Memory not allocated.\n");
            exit(0);
        }
    }

    // Fill the dictionary with words (omitted)

    WordCount* wordCounts = countWords(dictionary, DICTIONARY_SIZE);

    // Output the word counts (omitted)

    for(int i = 0; i < DICTIONARY_SIZE; i++) {
        free(dictionary[i]);
    }
    free(wordCounts);
    
    return 0;
}