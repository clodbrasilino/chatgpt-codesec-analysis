#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void printList(Node* head) {
    if (head == NULL) {
        printf("[]");
        return;
    }
    printf("[");
    Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]");
}

Node* copyList(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    Node* newHead = NULL;
    Node* current = head;
    while (current != NULL) {
        appendNode(&newHead, current->data);
        current = current->next;
    }
    return newHead;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

Node** generateAllSublists(Node* list, int* count) {
    if (list == NULL || count == NULL) {
        return NULL;
    }
    
    int length = 0;
    Node* current = list;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    
    int totalSublists = 1 << length;
    *count = totalSublists;
    
    Node** sublists = (Node**)malloc(totalSublists * sizeof(Node*));
    if (sublists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < totalSublists; i++) {
        sublists[i] = NULL;
    }
    
    for (int mask = 0; mask < totalSublists; mask++) {
        Node* sublist = NULL;
        current = list;
        int index = 0;
        
        while (current != NULL) {
            if (mask & (1 << index)) {
                appendNode(&sublist, current->data);
            }
            current = current->next;
            index++;
        }
        
        sublists[mask] = sublist;
    }
    
    return sublists;
}

void freeSublists(Node** sublists, int count) {
    if (sublists == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        freeList(sublists[i]);
    }
    free(sublists);
}

int main() {
    Node* list = NULL;
    appendNode(&list, 1);
    appendNode(&list, 2);
    appendNode(&list, 3);
    
    printf("Original list: ");
    printList(list);
    printf("\n\n");
    
    int count = 0;
    Node** sublists = generateAllSublists(list, &count);
    
    if (sublists != NULL) {
        printf("All sublists (%d total):\n", count);
        for (int i = 0; i < count; i++) {
            printf("Sublist %d: ", i + 1);
            printList(sublists[i]);
            printf("\n");
        }
        freeSublists(sublists, count);
    }
    
    freeList(list);
    
    return 0;
}