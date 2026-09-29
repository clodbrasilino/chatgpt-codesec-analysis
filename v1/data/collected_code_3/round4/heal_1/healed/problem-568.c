#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
} Dictionary;

Dictionary* createEmptyDictionary() {
    Dictionary* newDictionary = (Dictionary*)malloc(sizeof(Dictionary));
    if(newDictionary == NULL){
        return NULL;
    }
    strcpy(newDictionary->key, "");
    strcpy(newDictionary->value, "");
    return newDictionary;
}

Dictionary** createListOfEmptyDictionaries(int size) {
    Dictionary** listOfDictionaries = (Dictionary**)malloc(size * sizeof(Dictionary*));
    if(listOfDictionaries == NULL){
        return NULL;
    }
    for(int i = 0; i < size; i++) {
        listOfDictionaries[i] = createEmptyDictionary();
        if(listOfDictionaries[i] == NULL){
            for(int j = 0; j < i; j++) {
                free(listOfDictionaries[j]);
            }
            free(listOfDictionaries);
            return NULL;        
        }
    }
    return listOfDictionaries;
}

int main() {
    int size = 10;
    Dictionary** listOfDictionaries = createListOfEmptyDictionaries(size);
    if(listOfDictionaries == NULL){
        return -1;
    }
    for(int i = 0; i < size; i++) {
        printf("Dictionary %d: Key = %s, Value = %s\n", i, listOfDictionaries[i]->key, listOfDictionaries[i]->value);
    }
    for(int i = 0; i < size; i++) {
        free(listOfDictionaries[i]);
    }
    free(listOfDictionaries);
    return 0;
}