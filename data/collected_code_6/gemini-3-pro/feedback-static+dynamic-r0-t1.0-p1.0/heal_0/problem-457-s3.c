#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Sublist {
    Node* head;
    int length;
} Sublist;

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

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

Sublist* findMinLengthSublist(Sublist** sublists, int numSublists) {
    if (sublists == NULL || numSublists <= 0) {
        return NULL;
    }

    Sublist* minSublist = sublists[0];
    int minLength = -1;

    for (int i = 0; i < numSublists; ++i) {
        if (sublists[i] == NULL) {
            continue;
        }
        
        int currentLength = 0;
        Node* current = sublists[i]->head;
        while (current != NULL) {
            currentLength++;
            current = current->next;
        }
        
        sublists[i]->length = currentLength;

        if (minLength == -1 || currentLength < minLength) {
            minLength = currentLength;
            minSublist = sublists[i];
        }
    }

    return minSublist;
}

int main() {
    Sublist* sublists[3];
    for (int i = 0; i < 3; i++) {
        sublists[i] = (Sublist*)malloc(sizeof(Sublist));
        if (sublists[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                freeList(sublists[j]->head);
                free(sublists[j]);
            }
            exit(EXIT_FAILURE);
        }
    }

    sublists[0]->head = createNode(1);
    sublists[0]->head->next = createNode(2);
    sublists[0]->head->next->next = createNode(3);

    sublists[1]->head = createNode(4);
    sublists[1]->head->next = createNode(5);

    sublists[2]->head = createNode(6);
    
    Sublist* minSublist = findMinLengthSublist(sublists, 3);
    
    if (minSublist != NULL) {
        printf("Minimum length sublist starts with data: %d, length: %d\n", 
               minSublist->head ? minSublist->head->data : -1, 
               minSublist->length);
    }

    for (int i = 0; i < 3; ++i) {
        if (sublists[i] != NULL) {
            freeList(sublists[i]->head);
            free(sublists[i]);
        }
    }

    return 0;
}