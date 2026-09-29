#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

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

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

bool areConsecutive(Node* head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }
    
    Node* current = head;
    int length = 0;
    int min = current->data;
    int max = current->data;
    
    while (current != NULL) {
        if (current->data < min) min = current->data;
        if (current->data > max) max = current->data;
        length++;
        current = current->next;
    }
    
    if (max - min + 1 != length) {
        return false;
    }
    
    bool* seen = (bool*)calloc(length, sizeof(bool));
    if (seen == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    
    current = head;
    while (current != NULL) {
        int index = current->data - min;
        if (seen[index]) {
            free(seen);
            return false;
        }
        seen[index] = true;
        current = current->next;
    }
    
    free(seen);
    return true;
}

int main() {
    Node* head1 = NULL;
    appendNode(&head1, 5);
    appendNode(&head1, 2);
    appendNode(&head1, 4);
    appendNode(&head1, 3);
    appendNode(&head1, 1);
    
    printf("List 1 is %sconsecutive\n", areConsecutive(head1) ? "" : "not ");
    freeList(head1);
    
    Node* head2 = NULL;
    appendNode(&head2, 1);
    appendNode(&head2, 2);
    appendNode(&head2, 3);
    appendNode(&head2, 5);
    
    printf("List 2 is %sconsecutive\n", areConsecutive(head2) ? "" : "not ");
    freeList(head2);
    
    Node* head3 = NULL;
    appendNode(&head3, 1);
    appendNode(&head3, 1);
    appendNode(&head3, 2);
    
    printf("List 3 is %sconsecutive\n", areConsecutive(head3) ? "" : "not ");
    freeList(head3);
    
    Node* head4 = NULL;
    appendNode(&head4, 10);
    
    printf("List 4 is %sconsecutive\n", areConsecutive(head4) ? "" : "not ");
    freeList(head4);
    
    return 0;
}