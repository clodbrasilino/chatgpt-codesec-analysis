#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
    struct Node* tail;
};

void mergeFirstLast(struct List* list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return;
    }
    
    struct Node* first = list->head;
    struct Node* last = list->tail;
    
    while (first != last && first->next != last) {
        struct Node* temp = first->next;
        first->next = last->next;
        last->next = temp;
        
        first = temp;
        last = last->next;
        
        list->tail = last;
    }
}

int main() {
    struct List list;
    
    struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node3 = (struct Node*)malloc(sizeof(struct Node));
    
    node1->data = 1;
    node1->next = node2;
    node2->data = 2;
    node2->next = node3;
    node3->data = 3;
    node3->next = NULL;
    
    list.head = node1;
    list.tail = node3;
    
    mergeFirstLast(&list);
    
    struct Node* current = list.head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    
    return 0;
}