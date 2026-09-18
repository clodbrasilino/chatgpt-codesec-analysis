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
    dictionary->head = NULL;
    dictionary->size = 0;
    return dictionary;
}

int isEmpty(Dictionary* dictionary) {
    return dictionary->size == 0;
}

int main() {
    Dictionary* dictionary = createDictionary();
    if (isEmpty(dictionary)) {
        printf("The dictionary is empty\n");
    } else {
        printf("The dictionary is not empty\n");
    }
    return 0;
}