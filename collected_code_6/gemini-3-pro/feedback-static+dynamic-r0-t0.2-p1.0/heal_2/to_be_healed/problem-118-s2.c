#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* appendNode(Node* head, const char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    
    newNode->data = strdup(str);
    newNode->next = NULL;
    
    if (!head) {
        return newNode;
    }
    
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

void printList(Node* head) {
    if (!head) return;
    
    printf("[");
    Node* current = head;
    while (current) {
        printf("'%s'", current->data);
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

int main(void) {
    Node* head = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (scanf("%255s", buffer) == 1) {
        head = appendNode(head, buffer);
    }
    
    printList(head);
    freeList(head);
    
    return EXIT_SUCCESS;
}