#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->key = NULL;
    newNode->value = NULL;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    if (!newList) {
        return NULL;
    }
    newList->head = createNode();
    if (!newList->head) {
        free(newList);
        return NULL;
    }
    return newList;
}

List** createListOfDictionaries(int size) {
    List** listOfDictionaries = (List**)malloc(size * sizeof(List*));
    if (!listOfDictionaries) {
        return NULL;
    }
    for(int i = 0; i < size; i++) {
        listOfDictionaries[i] = createList();
        if (!listOfDictionaries[i]) {
            for (int j = 0; j < i; j++) {
                free(listOfDictionaries[j]->head);
                free(listOfDictionaries[j]);
            }
            free(listOfDictionaries);
            return NULL;
        }
    }
    return listOfDictionaries;
}

int main() {
    int size = 5;
    List** listOfDictionaries = createListOfDictionaries(size);
    if (!listOfDictionaries) {
        return -1;
    }
    // Use the list of dictionaries...
    // Don't forget to free the memory!
    for(int i = 0; i < size; i++) {
        free(listOfDictionaries[i]->head);
        free(listOfDictionaries[i]);
    }
    free(listOfDictionaries);
    return 0;
}