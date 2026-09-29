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
    newNode->key = NULL;
    newNode->value = NULL;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    newList->head = createNode();
    return newList;
}

List** createListOfDictionaries(int size) {
    List** listOfDictionaries = (List**)malloc(size * sizeof(List*));
    for(int i = 0; i < size; i++) {
        listOfDictionaries[i] = createList();
    }
    return listOfDictionaries;
}

int main() {
    int size = 5;
    List** listOfDictionaries = createListOfDictionaries(size);
    // Use the list of dictionaries...
    // Don't forget to free the memory!
    for(int i = 0; i < size; i++) {
        free(listOfDictionaries[i]->head);
        free(listOfDictionaries[i]);
    }
    free(listOfDictionaries);
    return 0;
}