#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));
    if(dictionary == NULL) {
        return NULL;
    }
    dictionary->head = NULL;
    dictionary->size = 0;
    return dictionary;
}

int isEmpty(Dictionary* dictionary) {
    if(dictionary == NULL) {
        return 0;
    }
    return dictionary->size == 0;
}

int main() {
    Dictionary* dictionary = createDictionary();
    if (dictionary == NULL || isEmpty(dictionary)) {
        printf("The dictionary is empty\n");
    } else {
        printf("The dictionary is not empty\n");
    }
    free(dictionary);
    return 0;
}