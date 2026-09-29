#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct List {
    struct Node* head;
    int size;
} List;

List* createList() {
    List* newList = (List*) malloc(sizeof(List));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addNode(List* list, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

List* findShortestList(List** lists, int size) {
    if(size == 0) return NULL;
    List* shortestList = lists[0];
    for(int i = 1; i < size; i++) {
        if(lists[i]->size < shortestList->size) {
            shortestList = lists[i];
        }
    }
    return shortestList;
}

int main() {
    int numLists = 3;
    List* lists[numLists];
    
    for(int i = 0; i < numLists; i++) {
        lists[i] = createList();
        for(int j = i; j < 5; j++) {
            addNode(lists[i], j);
        }
    }
    
    List* shortestList = findShortestList(lists, numLists);
    printf("Shortest list size: %d\n", shortestList->size);
    
    for(int i = 0; i < numLists; i++) {
        free(lists[i]);
    }

    return 0;
}
