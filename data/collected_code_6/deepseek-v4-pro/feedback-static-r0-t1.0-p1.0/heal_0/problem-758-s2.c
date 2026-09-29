#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

void appendToList(List* list, int data) {
    if (list == NULL) return;
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void freeList(List* list) {
    if (list == NULL) return;
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

bool listsEqual(List* list1, List* list2) {
    if (list1 == NULL || list2 == NULL) return false;
    Node* current1 = list1->head;
    Node* current2 = list2->head;
    
    while (current1 != NULL && current2 != NULL) {
        if (current1->data != current2->data) return false;
        current1 = current1->next;
        current2 = current2->next;
    }
    
    return current1 == NULL && current2 == NULL;
}

int countUniqueLists(List** lists, int count) {
    if (lists == NULL || count <= 0) return 0;
    
    int uniqueCount = 0;
    bool* seen = (bool*)calloc(count, sizeof(bool));
    if (seen == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < count; i++) {
        if (seen[i]) continue;
        
        uniqueCount++;
        for (int j = i + 1; j < count; j++) {
            if (!seen[j] && listsEqual(lists[i], lists[j])) {
                seen[j] = true;
            }
        }
    }
    
    free(seen);
    return uniqueCount;
}

int main() {
    int uniqueLists = 0;
    
    List* list1 = createList();
    appendToList(list1, 1);
    appendToList(list1, 2);
    appendToList(list1, 3);
    
    List* list2 = createList();
    appendToList(list2, 1);
    appendToList(list2, 2);
    appendToList(list2, 3);
    
    List* list3 = createList();
    appendToList(list3, 4);
    appendToList(list3, 5);
    
    List* list4 = createList();
    appendToList(list4, 1);
    appendToList(list4, 2);
    
    List* list5 = createList();
    appendToList(list5, 4);
    appendToList(list5, 5);
    
    List* lists[] = {list1, list2, list3, list4, list5};
    
    uniqueLists = countUniqueLists(lists, 5);
    printf("Number of unique lists: %d\n", uniqueLists);
    
    freeList(list1);
    freeList(list2);
    freeList(list3);
    freeList(list4);
    freeList(list5);
    
    return 0;
}